import json
import requests
import numpy as np;
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



# # Example: Generate some dummy EEG data
# num_samples = 10  # Number of EEG samples
# num_channels = 8  # EEG channels
# sample_rate = 250  # Samples per second

# # Creating a list of EEG samples
# eeg_data = []
# for _ in range(num_samples):
#     sample = {f"eeg {i+1}": np.random.randn(sample_rate).tolist() for i in range(num_channels)}
#     eeg_data.append(sample)

# print(len(eeg_data));
# print(len(eeg_data[0]));

# # Save to JSON file
# with open("eeg_data.json", "w") as f:
#     json.dump(eeg_data, f, indent=4)

# print("EEG data saved successfully!")

for i in range(251):
    print(str(i) + " ,", end="");