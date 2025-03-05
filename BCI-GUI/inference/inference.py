import argparse;
from torcheeg.models import EEGNet;
import os;
import torch;
from torch import nn;
import pandas as pd;
from typing import List;
import requests;

# Global variables
profile: nn.Module = None;
profile_name: str = "";
eeg_buffer: pd.DataFrame = None;

# Customizable constants
MODEL_PATH = "./models"
CHANNEL_COUNT = 8;
WINDOW_LENGTH = 250;
SAMPLE_RATE = 250;
DEVICE = "cuda" if torch.cuda.is_available() else "cpu";
CLASSES: List[str] = ["up", "down", "left", "right", "baseline"];
API_BASE_URL = "https://bciproject-api.onrender.com/api/profile";

os.makedirs(MODEL_PATH, exist_ok=True);

# [UTILITY START]

def upload_model():
    global profile_name, profile, eeg_buffer;

    data = {"name": f"{profile_name}"};

    files = {
        "model_data": open(f"BCI-GUI/inference/models/{profile_name}.onnx", "rb"),
        "ica_model": open(f"BCI-GUI/inference/models/{profile_name}.dat", "rb"),
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
    
    profile = None;
    profile_name = "";
    eeg_buffer = None;
    pass;

def api_has_model(profileName: str) -> bool:
    response = requests.get(f"{API_BASE_URL}/profile", params={"profileName": f"{profileName}"});
    return response.status_code == 200;
        
# [UTILITY END]

# [START DEFINITIONS]
create_docs: str = """
    Creates a new model instance to start training.
    `python inference.py create <PROFILE_NAME>`

    If a model before this one was already in created and had started training, it will be overwritten. This method simply creates a new instance and 
    sets it as the current model to train. When `train()` is called, the most recently created model with `create()` will be trained.

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
    
    global profile;
    global profile_name;
    global eeg_buffer;

    profile = EEGNet(
        chunk_size=WINDOW_LENGTH,
        dropout=0.25,
        num_classes=len(CLASSES),
        num_electrodes=CHANNEL_COUNT,
    ).to(DEVICE);

    profile.train();
    profile_name = profileName;
    eeg_buffer = pd.DataFrame(columns=[f"electrode_{elec + 1}" for elec in range(CHANNEL_COUNT)], dtype=pd.Float32Dtype())

create.__doc__ = create_docs;


train_docs: str = """
    Will add a sample of size ({CHANNEL_COUNT}) to the window and then feed the window to the model. When training, pass the stream 
    `python inference.py train 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8  <up | down | left | right | baseline>`

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
def train(input: List[float], target: str) -> None:
    global profile, eeg_buffer;

    if len(input) != CHANNEL_COUNT: raise TypeError(f"\nThe input length is invalid. \nActual Length: {len(input)}\nExpected Length: {CHANNEL_COUNT}");
    if not all(isinstance(x, (int, float)) for x in input): raise TypeError("\nThe input type is invalid. The elements are not numbers.");
    if (profile is None) : raise ValueError("\nNo model loaded! Use 'create' first.");

    new_row = pd.DataFrame([input], columns=[f"electrode_{i+1}" for i in range(CHANNEL_COUNT)]);
    eeg_buffer = pd.concat([eeg_buffer, new_row], ignore_index=True);

    if len(eeg_buffer) > WINDOW_LENGTH:
        eeg_buffer = eeg_buffer.iloc[1:].reset_index(drop=True);

    # Train only when the buffer reaches 250 samples
    if len(eeg_buffer) == WINDOW_LENGTH:
    
        X = torch.tensor(eeg_buffer.values, dtype=torch.float32).unsqueeze(0).unsqueeze(0).to(DEVICE)  # Shape: (1, 1, CHANNEL_COUNT, WINDOW_SIZE)
        y = torch.tensor([CLASSES.index(target)], dtype=torch.long).to(DEVICE)

        criterion = nn.CrossEntropyLoss();
        optimizer = torch.optim.Adam(profile.parameters(), lr=0.001);

        profile.train();
        optimizer.zero_grad();

        preds = profile(X);
        loss = criterion(preds, y);

        loss.backward();
        optimizer.step();

        print(f"Training Step: Loss = {loss.item():.4f}");
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
def export() -> None:

    global profile;
    global profile_name;

    if profile == None:
        raise FileNotFoundError("No Profile is currently in training. call `inference.py create <PROFILE_NAME>`.\n");

    profile.eval();
    
    torch.onnx.export(
        profile.to(DEVICE),
        torch.randn(1, 1, CHANNEL_COUNT, WINDOW_LENGTH).to(DEVICE), # (1 sample, 1 channel, electrode count, window/chunk size)
        f"./models/{profile_name}.onnx",
        export_params=True,
        opset_version=11,
        input_names=["input"],
        output_names=["output"],
        dynamic_axes={'input': {0: 'batch_size'}, 'output': {0: 'batch_size'}} # Allow dynamic batch size
    );

    upload_model();
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

export_parser = subparsers.add_parser("export", help="Export trained model");
export_parser.add_argument("profile_name", type=str, help="Profile Name");

args = parser.parse_args();

# Handle different commands separately
if args.command == "create":
    create(args.profile_name);

elif args.command == "train":
    train(args.data, args.target);

elif args.command == "export":
    export();
# [END PARSER]
