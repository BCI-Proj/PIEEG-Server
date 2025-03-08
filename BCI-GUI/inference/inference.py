import argparse
from torcheeg.models import EEGNet
import os
import torch
from torch import nn
import pandas as pd
from typing import List
import requests

# Customizable constants
MODEL_PATH = "./models"
ICA_MODEL_PATH = "./ica_models"
DATA_PATH = "./data"  # Folder to persist training data
CHANNEL_COUNT = 8
WINDOW_LENGTH = 250
SAMPLE_RATE = 250

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"
CLASSES: List[str] = ["up", "down", "left", "right", "baseline"]
API_BASE_URL = "https://bciproject-api.onrender.com/api/profile"

os.makedirs(MODEL_PATH, exist_ok=True)
os.makedirs(ICA_MODEL_PATH, exist_ok=True)
os.makedirs(DATA_PATH, exist_ok=True)

# [UTILITY START]
def upload_model(profileName):
    data = {"name": f"{profileName}"}

    files = {
        "model_data": open(f"{MODEL_PATH}/{profileName}.onnx", "rb"),
        "ica_model": open(f"{ICA_MODEL_PATH}/{profileName}.fif", "rb"),
    }

    response = requests.post(f"{API_BASE_URL}/create", data=data, files=files)

    if response.status_code == 200:
        print("Profile created successfully!")
        print(response.json())
    elif response.status_code == 409:
        print("Profile already exists.")
    else:
        print(f"Error {response.status_code}: {response.text}")

def api_has_model(profileName: str) -> bool:
    response = requests.get(f"{API_BASE_URL}/profile", params={"profileName": profileName})
    return response.status_code == 200
# [UTILITY END]

# [START DEFINITIONS]
create_docs = """
    Creates a new model instance to start training.
    `python inference.py create <PROFILE_NAME>`

    This will create a new instance of the model and initialize a CSV file to store training data.
    
    Parameters
    ----------
    profileName : str
        The name of the profile to create. This will also be used for the exported ONNX file.
        
    Raises
    ------
    FileExistsError
        If a profile with the same name exists.
"""
def create(profileName: str) -> None:

    if os.path.isfile(f"{MODEL_PATH}/{profileName}.onnx") or api_has_model(profileName):
        raise FileExistsError(f"The profile {profileName} already exists")

    # Initialize a CSV file with columns for EEG data and a target label.
    columns = [f"electrode_{i+1}" for i in range(CHANNEL_COUNT)] + ["target"]
    empty_df = pd.DataFrame(columns=columns)
    empty_df.to_csv(f"{DATA_PATH}/{profileName}_eeg.csv", index=False)
    print(f"Created new profile '{profileName}' with an empty training data file.")

create.__doc__ = create_docs

train_docs = f"""
    Appends a new training sample to the persistent data file.
    
    Usage:
      python inference.py train 0.1 0.2 ... 0.8 <up | down | left | right | baseline>
      
    Parameters
    ----------
    data : List[float]
        A single sample of EEG data with {CHANNEL_COUNT} channels.
    target : str
        The corresponding label for the sample. Valid labels: {", ".join(CLASSES)}.
        
    Raises
    ------
    TypeError
        If the input does not have the correct number of channels or the types are not numbers.
    ValueError
        If no model is loaded. Use 'create' first.
"""
def train(input: List[float], target: str, profileName: str) -> None:

    if len(input) != CHANNEL_COUNT:
        raise TypeError(f"Input length invalid. Expected {CHANNEL_COUNT} channels.")
    if not all(isinstance(x, (int, float)) for x in input):
        raise TypeError("All elements of input must be numbers.")
    if target not in CLASSES:
        raise ValueError(f"Target must be one of {CLASSES}")

    csv_path = f"{DATA_PATH}/{profileName}_eeg.csv"
    df = pd.read_csv(csv_path)

    # Create a new row with the EEG data and target label
    new_row = pd.DataFrame([input + [target]], columns=[f"electrode_{i+1}" for i in range(CHANNEL_COUNT)] + ["target"])
    df = pd.concat([df, new_row], ignore_index=True)
    df.to_csv(csv_path, index=False)
    print(f"Appended sample to training data. Total samples: {len(df)}.")

train.__doc__ = train_docs

export_docs = f"""
    Loads the persistent training data, trains the model on all the collected samples in one go, 
    exports the model as an ONNX file, and uploads it along with its ICA model.
    
    Usage:
      python inference.py export <PROFILE_NAME>
    
    Parameters
    ----------
    None
"""
def export(profileName) -> None:

    profile: nn.Module = EEGNet(
        chunk_size=WINDOW_LENGTH,
        dropout=0.25,
        num_classes=len(CLASSES),
        num_electrodes=CHANNEL_COUNT,
    ).to(DEVICE);

    csv_path = f"{DATA_PATH}/{profileName}_eeg.csv";
    df = pd.read_csv(csv_path);
    if df.empty:
        raise ValueError("No training data available. Please call 'train' first.");

    feature_cols = [f"electrode_{i+1}" for i in range(CHANNEL_COUNT)];
    X_data = df[feature_cols].values.astype('float32')  # Shape: (num_samples, CHANNEL_COUNT)
    y_data = df["target"].apply(lambda x: CLASSES.index(x)).values.astype('int64');

    X_tensor = torch.tensor(X_data, dtype=torch.float32).to(DEVICE);
    y_tensor = torch.tensor(y_data, dtype=torch.long).to(DEVICE);

    X_tensor = X_tensor.unsqueeze(1).unsqueeze(-1);

    criterion = nn.CrossEntropyLoss();
    optimizer = torch.optim.Adam(profile.parameters(), lr=0.001);
    num_epochs = 10;
    profile.train();
    for epoch in range(num_epochs):
        optimizer.zero_grad();
        preds = profile(X_tensor);
        loss = criterion(preds, y_tensor);
        loss.backward();
        optimizer.step();
        print(f"Epoch {epoch+1}/{num_epochs} - Loss: {loss.item():.4f}");

    profile.eval();
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

    upload_model();
    print(f"Exported and uploaded profile '{profileName}'.");

export.__doc__ = export_docs
# [END DEFINITIONS]

parser = argparse.ArgumentParser(description="Inference for classifying EEG signals")
subparsers = parser.add_subparsers(dest="command", required=True, help="Available commands")

create_parser = subparsers.add_parser("create", help="Create a new EEG profile")
create_parser.add_argument("profile_name", type=str, help="Creates a profile under <profile_name>")

train_parser = subparsers.add_parser("train", help="Append training data sample")
train_parser.add_argument("data", type=float, nargs="+", help="List of EEG data values")
train_parser.add_argument("target", type=str, help="Target class for the sample (up, down, left, right, baseline)")
train_parser.add_argument("profile_name", type=str, help="The profile name being made")

export_parser = subparsers.add_parser("export", help="Train on all persisted data and export the model")
export_parser.add_argument("profile_name", type=str, help="The profile name being made")

args = parser.parse_args()

if args.command == "create":
    create(args.profile_name);
elif args.command == "train":
    train(args.data, args.target, args.profile_name);
elif args.command == "export":
    export(args.profile_name);
