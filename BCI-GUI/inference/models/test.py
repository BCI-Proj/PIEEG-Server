from typing import List
import numpy as np;
import requests
import argparse;
import mne;

url = "https://bciproject-api.onrender.com/api/profile";


# data = {"name": "Raph"};

# files = {
#     "model_data": open("BCI-GUI/inference/models/test123.onnx", "rb"),
#     "ica_model": open("BCI-GUI/inference/models/test.dat", "rb"),
# }

# response = requests.post(f"{url}/create", data=data, files=files);

# # Print the response
# if response.status_code == 200:
#     print("Profile created successfully!")
#     print(response.json())  # If JSON is returned
# elif response.status_code == 409:
#     print("Profile already exists.")
# else:
#     print(f"Error {response.status_code}: {response.text}")


# def api_has_model(profileName: str) -> bool:
#     response = requests.get(f"{url}/profile", params={"profileName": f"{profileName}"});
#     return response.status_code == 200;
        

# print(api_has_model("raph1"));

# print(['eeg'] * 8);


# data = [1,2,3,4,5,6,7,8]
# eeg_buffer = numpy.array([[eeg] for eeg in data]);

# print(eeg_buffer);
# print(numpy.array(eeg_buffer));

eeg_buffer = None;

# def test1():
#     global eeg_buffer
#     eeg_buffer = [[]] * 8;

# def test(data: List[int]):
#     global eeg_buffer
#     if (len(eeg_buffer[0]) == 0):
#         eeg_buffer = np.array([[eeg] for eeg in data]);
#     else:
#         eeg_buffer = np.append(eeg_buffer, [[eeg] for eeg in data], axis=1);
    
#     print(eeg_buffer.data.tolist())

# test1();

# test([1, 2, 3, 4, 5, 6, 7, 8]);
# test([9, 9, 9, 9, 9, 9, 9, 9]);


# eeg_buffer = np.empty((8, 1));

# print(eeg_buffer)

# Convert the input data to a column vector with shape (CHANNEL_COUNT, 1)
# sample_column = np.array([1, 2, 3, 4, 5, 6, 7, 8]).reshape(8, 1)


# for i in range(2):
#     # If the buffer is uninitialized or empty, assign it to the new sample
#     if eeg_buffer is None or eeg_buffer.shape[1] == 0:
#         eeg_buffer = sample_column
#     else:
#         # Append the new sample as a new column
#         eeg_buffer = np.concatenate((eeg_buffer, sample_column), axis=1);

# print(eeg_buffer)

# [START PARSER]

name: str;

def test1(nameParam):
    global name;
    name = nameParam;

def test2():
    global name;
    print(name)

parser = argparse.ArgumentParser(description="Inference for classifying EEG signals");
subparsers = parser.add_subparsers(dest="command", required=True, help="Available commands");

create_parser = subparsers.add_parser("create", help="Create a new EEG profile");
create_parser.add_argument("name", type=str);

train_parser = subparsers.add_parser("train", help="Train a model using EEG data");

args = parser.parse_args();

# Handle different commands separately
if args.command == "create":
    test1(args.name)

elif args.command == "train":
    test2();

# [END PARSER]
