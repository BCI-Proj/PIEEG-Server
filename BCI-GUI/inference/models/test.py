import requests

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


def api_has_model(profileName: str) -> bool:
    response = requests.get(f"{url}/profile", params={"profileName": f"{profileName}"});
    return response.status_code == 200;
        

print(api_has_model("raph1"));