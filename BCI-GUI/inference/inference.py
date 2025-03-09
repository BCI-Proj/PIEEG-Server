import tqdm;
import argparse;
from torcheeg.models import EEGNet;
import os;
import time;
import torch;
from torch import nn;
import json;
from typing import List;
import requests
from torch.utils.data.dataloader import DataLoader;
import tqdm.auto;

# Customizable constants
EPOCH_COUNT = 50;
MODEL_PATH = "./models"
CHANNEL_COUNT = 8;
WINDOW_LENGTH = 250;
SAMPLE_RATE = 250;
DEVICE = "cuda" if torch.cuda.is_available() else "cpu";
CLASSES: List[str] = ["up", "down", "left", "right", "baseline"];
API_BASE_URL = "https://bciproject-api.onrender.com/api/profile";

os.makedirs(MODEL_PATH, exist_ok=True);

# [UTILITY START]

def upload_model(profileName):
    time.sleep(1);
    data = {"name": f"{profileName}"};

    files = {
        "model_data": open(f"{MODEL_PATH}/{profileName}.onnx", "rb"),
        "ica_model": open(f"{MODEL_PATH}/{profileName}.json", "rb"), # For now, I'll instead send the json that holds the data
    };

    response = requests.post(f"{API_BASE_URL}/create", data=data, files=files);

    # Print the response
    if response.status_code == 200:
        print("Profile created successfully!");
        print(response.json());
    elif response.status_code == 409:
        print("Profile already exists.");
    else:
        print(f"Error {response.status_code}: {response.text}");
    
    pass;

def api_has_model(profileName: str) -> bool:
    response = requests.get(f"{API_BASE_URL}/profile", params={"profileName": f"{profileName}"});
    return response.status_code == 200;
        
class EEGDataset(torch.utils.data.Dataset):
    def __init__(self, json_path):
        with open(json_path, "r") as f:
            self.data = json.load(f);
        
        self.labels = {cls: idx for idx, cls in enumerate(CLASSES)};

    def __len__(self):
        return len(self.data);

    def __getitem__(self, idx):
        sample = self.data[idx];
        X = torch.tensor([sample[f"eeg-{i+1}"] for i in range(CHANNEL_COUNT)], dtype=torch.float32).unsqueeze(0);
        y = torch.tensor(self.labels[sample["target"]], dtype=torch.long);
        return X, y

# [UTILITY END]

# [START DEFINITIONS]
create_docs: str = """
    Creates the json file that will persist EEG Data for given model.
    `python inference.py create <PROFILE_NAME>`

    Parameters
    ----------
    profileName : str
        The name of the profile to create. This will also be the name of the exported onnx file.        
        
    Raises
    ------
    FileExistsError
        If a profile with the same name exists, this error will be raised.
""";
def create(profileName: str) -> None:

    if os.path.isfile(f"./models/{profileName}.onnx") or api_has_model(profileName): 
        raise FileExistsError(f"The profile {profileName} already exists");

    with open(f'{MODEL_PATH}/{profileName}.json', 'w') as f:
        json.dump([], f);
create.__doc__ = create_docs;


train_docs: str = """
    Will add a sample of size ({CHANNEL_COUNT}) to the window and then feed the window to the model. When training, pass the stream 
    `python inference.py train 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8  <up | down | left | right | baseline> <PROFILE_NAME>`

    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    input : List[float] 
        This list has to correspond to the size of CHANNEL COUNT ({CHANNEL_COUNT}). It represents a single sample of EEG data.

    target : str 
        This is the corresponding label for the EEG data input. For our project this is {CLASSES}.
        
    Raises
    ------
    TypeError
        If the type of the input is incorrect in any way this will be thrown, reffer to the messages in the error.
""".format(CHANNEL_COUNT=CHANNEL_COUNT, CLASSES=", ".join(CLASSES));
def train(input: List[float], target: str, profileName: str) -> None:
    pass;   
train.__doc__ = train_docs;

export_docs: str = """
    Will export the currently trained model under `inference/models/<PROFILE_NAME>.onnx`. If file of same name exists, will overwrite.
    `python inference.py export <PROFILE_NAME>`
    
    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    None
        
    Returns
    ----------
    None
""".format(CHANNEL_COUNT=CHANNEL_COUNT, CLASSES=", ".join(CLASSES));
def export(profileName) -> None:
    dataset = EEGDataset(f"{MODEL_PATH}/{profileName}.json")
    dataloader = DataLoader(dataset, batch_size=16, shuffle=True)

    profile = EEGNet(
        chunk_size=WINDOW_LENGTH,
        dropout=0.25,
        num_classes=len(CLASSES),
        num_electrodes=CHANNEL_COUNT,
    ).to(DEVICE)

    criterion = nn.CrossEntropyLoss();
    optimizer = torch.optim.Adam(profile.parameters(), lr=0.001);

    profile.train();
    for epoch in tqdm.auto.tqdm(range(EPOCH_COUNT)):  
        epoch_loss = 0.0;
        for X, y in dataloader:
            X, y = X.to(DEVICE), y.to(DEVICE);
            optimizer.zero_grad();
            preds = profile(X);
            loss = criterion(preds, y);
            loss.backward();
            optimizer.step();
            epoch_loss += loss.item();
        print(f"Epoch {epoch+1}: Loss = {epoch_loss / len(dataloader):.4f}");
 
    torch.onnx.export(
        profile.to(DEVICE),
        torch.randn(1, 1, CHANNEL_COUNT, WINDOW_LENGTH).to(DEVICE), 
        f"{MODEL_PATH}/{profileName}.onnx",
        export_params=True,
        opset_version=11,
        input_names=["input"],
        output_names=["output"],
        dynamic_axes={'input': {0: 'batch_size'}, 'output': {0: 'batch_size'}} 
    )

    upload_model(profileName);
export.__doc__ = export_docs;
# [END DEFINITIONS]


# [START PARSER]
parser = argparse.ArgumentParser(description="Inference for classifying EEG signals");
subparsers = parser.add_subparsers(dest="command", required=True, help="Available commands");

create_parser = subparsers.add_parser("create", help="Create a new EEG profile");
create_parser.add_argument("profile_name", type=str, help="Create's a profile under <profile_name>");

train_parser = subparsers.add_parser("train", help="Train a model using EEG data");
train_parser.add_argument("data", type=float, nargs="+", help="List of EEG data values");
train_parser.add_argument("target", type=str, help="The target class for training. (e.g. left, up, right, ...)")
train_parser.add_argument("profile_name", type=str, help="Profile Name");

export_parser = subparsers.add_parser("export", help="Export trained model");
export_parser.add_argument("profile_name", type=str, help="Profile Name");

args = parser.parse_args();

# Handle different commands separately
if args.command == "create":
    create(args.profile_name);

elif args.command == "train":
    train(args.data, args.target, args.profile_name);

elif args.command == "export":
    export(args.profile_name);
# [END PARSER]
