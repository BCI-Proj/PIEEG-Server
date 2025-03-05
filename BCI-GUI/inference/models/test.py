import numpy
import pandas as pd;

ARTIFACT_COUNT = 7;

# I need to make a method that will be called mutliple times that will populate
# A numpy array with shape ()

eeg_buffer = pd.DataFrame(columns=[f"electrode_{elec + 1}" for elec in range(ARTIFACT_COUNT)], dtype=pd.Float32Dtype());




artifact_names = ["jaw_clench", "eyes_blink", "eyes_closed", "eye_movement", "eyes_open", "deep_breathing", "head_movement"];
profile_name: str = "";
columns = ["timestamp"] + [f"ch-{i+1}" for i in range(8)] + ["artifact"]
eeg_buffer = pd.DataFrame(columns=columns)

print(artifact_names)
print(profile_name)
print(columns)
print(eeg_buffer)