import argparse
from typing import List
import numpy as np
import os
import mne
import requests

CHANNEL_COUNT = 8
SAMPLE_RATE = 250
CH_NAMES = [f'EEG {i}' for i in range(CHANNEL_COUNT)]
CH_TYPES = ['eeg'] * CHANNEL_COUNT
NUM_COMPONENTS = 0.999999;
ICA_MODEL_DIR = "./ica_models"
API_BASE_URL = "https://bciproject-api.onrender.com/api/profile"

def get_buffer_filepath(profile: str) -> str:
    os.makedirs(os.path.join(ICA_MODEL_DIR), exist_ok=True);
    return os.path.join(ICA_MODEL_DIR, f"{profile}_eeg.npy")

def save_buffer(buffer: np.ndarray, profile: str) -> None:
    np.save(get_buffer_filepath(profile), buffer)

def load_buffer(profile: str) -> np.ndarray:
    filepath = get_buffer_filepath(profile)
    if os.path.exists(filepath):
        return np.load(filepath, allow_pickle=True)
    else:
        return np.empty((CHANNEL_COUNT, 0))

# [START DEFINITIONS]

create_docs = """
    Creates a new ICA model instance.

    Parameters
    ----------
    profileName : str
        The name of the profile to create. This will also be the name of the exported file.

    Raises
    ------
    FileExistsError
        If a profile with the same name exists.
"""
def create(profileName: str) -> None:
    # Check if the model already exists
    if os.path.isfile(os.path.join(ICA_MODEL_DIR, f"{profileName}.fif")) or api_has_model(profileName):
        raise FileExistsError(f"The profile {profileName} already exists")

    eeg_buffer = np.empty((CHANNEL_COUNT, 0))
    save_buffer(eeg_buffer, profileName)
create.__doc__ = create_docs

record_docs = f"""
    Adds a sample of size ({CHANNEL_COUNT}) to a persistent EEG buffer.
    When `export()` is called, the collected data will be fit to an ICA model and saved to a `.fif` file.

    Parameters
    ----------
    data : List[float]
        A single sample of EEG data with {CHANNEL_COUNT} channels.

    Raises
    ------
    TypeError
        If the input does not have the correct number of channels.
"""
def record(data: List[float], profileName) -> None:
    if len(data) != CHANNEL_COUNT:
        raise TypeError("Incorrect Channel Count.")

    eeg_buffer = load_buffer(profileName)
    sample_column = np.array(data).reshape(CHANNEL_COUNT, 1)
    
    # Append the new sample as a new column.
    if eeg_buffer.size == 0:
        eeg_buffer = sample_column
    else:
        eeg_buffer = np.concatenate((eeg_buffer, sample_column), axis=1)
    
    # Save the updated buffer.
    save_buffer(eeg_buffer, profileName)
    return
record.__doc__ = record_docs

export_docs = """
    Loads the recorded EEG data, creates an MNE Raw object, fits an ICA model, and exports the ICA model as a .fif file.
    The EEG data is retrieved from persistent storage.

    Raises
    ------
    ValueError
        If no EEG data has been recorded.
"""
def export(profileName) -> None:
    
    # Load the persistent EEG buffer.
    eeg_buffer = load_buffer(profileName)
    
    if eeg_buffer.size == 0:
        raise ValueError("No EEG data recorded. Please record data before exporting.")
    
    info = mne.create_info(ch_names=CH_NAMES, sfreq=SAMPLE_RATE, ch_types=CH_TYPES, verbose=True)
    raw = mne.io.RawArray(eeg_buffer, info=info)
    raw.filter(l_freq=1.0, h_freq=None, fir_design='firwin')
    
    ica = mne.preprocessing.ICA(n_components=NUM_COMPONENTS, method="fastica", random_state=42, verbose=True)
    
    print("This is raw:");
    for i in raw:
        print(i);
    print("\n");
    ica.fit(raw)
    
    eog_inds, eog_scores = ica.find_bads_eog(raw)
    ecg_inds, ecg_scores = ica.find_bads_ecg(raw)
    emg_inds, emg_scores = ica.find_bads_muscle(raw)
    
    print(f"Detected EOG artifacts: {eog_scores}")
    print(f"Detected ECG artifacts: {ecg_scores}")
    print(f"Detected EMG artifacts: {emg_scores}")
    
    ica.exclude = eog_inds + ecg_inds + emg_inds

    ica.save(os.path.join(ICA_MODEL_DIR, f"{profileName}.fif"))
export.__doc__ = export_docs

def api_has_model(profileName: str) -> bool:
    response = requests.get(f"{API_BASE_URL}/profile", params={"profileName": profileName})
    return response.status_code == 200
# [END DEFINITIONS]

# [START PARSER]
parser = argparse.ArgumentParser(description="Inference for identifying independent components.")
subparsers = parser.add_subparsers(dest="command", required=True, help="Available commands")

# CREATING
create_parser = subparsers.add_parser("create", help="Create a new ICA model instance")
create_parser.add_argument("profile_name", type=str, help="Name of the model profile")

# RECORDING
record_parser = subparsers.add_parser("record", help="Record artifact EEG sample.")
record_parser.add_argument("data", type=float, nargs="+", help="List of EEG data values")
record_parser.add_argument("profile_name", type=str, help="Name of profile")

# EXPORTING
export_parser = subparsers.add_parser("export", help="Export the trained ICA model")
export_parser.add_argument("profile_name", type=str, help="Name of profile")

args = parser.parse_args()
if args.command == "create":
    create(args.profile_name)
elif args.command == "record":
    record(args.data, args.profile_name)
elif args.command == "export":
    export(profileName=args.profile_name)
# [END PARSER]
