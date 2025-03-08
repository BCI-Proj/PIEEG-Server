"""
    This file will be used to load an ICA model

    ```python
    >> load("profile1");

    >> clean([0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8]);
    ```
"""

import argparse;
import socket;
import pickle;
import mne;
import mne;
from typing import List;

HOST = '192.168.50.61';
PORT = 5001;
MODELS_PATH = "./ica_models";
SAMPLE_RATE = 250;

# [START DEFINITIONS]


load_docs: str = """
    Loads an ICA model. 

    Parameters
    ----------
    profileName : str
        The name of the profile to create. This will also be the name of the exported file.        
        
    Raises
    ------
""";
def load(profileName: str) -> None:
    return mne.preprocessing.read_ica(f"{MODELS_PATH}/{profileName}.fif");
load.__doc__ = load_docs;

# [END DEFINITIONS]


def connect(profileName):
    
    ica = load(profileName=profileName);

    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.bind((HOST, PORT))
    server_sock.listen()
    print(f"ICA Service running on {HOST}:{PORT}")

    def process_eeg(eeg_data):
        # Assuming eeg_data is a NumPy array of shape (n_channels, n_samples)
        info = mne.create_info(ch_names=[f'EEG {i}' for i in range(eeg_data.shape[0])],
                            sfreq=SAMPLE_RATE, ch_types=['eeg'] * eeg_data.shape[0])
        raw = mne.io.RawArray(eeg_data, info)
        # Optionally, apply filtering etc.
        # Apply ICA cleaning
        ica.apply(raw)
        # Return the cleaned data as a NumPy array
        return raw.get_data()

    while True:
        conn, addr = server_sock.accept()
        print("Connected by", addr)
        with conn:
            data = b""
            # Read the incoming data length (this example assumes the entire object is sent at once)
            while True:
                packet = conn.recv(4096)
                if not packet:
                    break
                data += packet
            if data:
                # Deserialize the EEG data (assumed to be sent as a pickled NumPy array)
                eeg_data = pickle.loads(data)
                print("Received EEG data with shape", eeg_data.shape)
                cleaned_data = process_eeg(eeg_data)
                # Serialize and send back the cleaned data
                conn.sendall(pickle.dumps(cleaned_data))


parser = argparse.ArgumentParser(description="Load and use a model");
subparsers = parser.add_subparsers(dest="command", required=True, help="Available commands");

create_parser = subparsers.add_parser("connect", help="Loads a model");
create_parser.add_argument("name", type=str);

args = parser.parse_args();

# Handle different commands separately
if args.command == "connect":
    connect(args.name)
