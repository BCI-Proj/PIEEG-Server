"""
    ICA (independent component analysis), 
    in this paradigm will be used to reduce the noise from artifacts of our EEG readings. 
    Different artifacts like EOG, EMG, breathing artifacts and even power lines produce noise alongside our source frequencies.
    ICA aims to identify these different independent sources and filter them out to clean our source and reduce noise.
    
    The paper written by individuals from Graz University of Technology, Austria, (C. Brunner1, R. Leeb, G. R. Müller-Putz, A. Schlögl, and G.Pfurtscheller)
    detailed how they went about building a dataset for their competition which brought EOG artifacts to our attention and how noise may play a great role in the accuracy of our model.

    [The Paper - BCI Competition 2008](https://www.bbci.de/competition/iv/desc_2a.pdf)

    These methods will be used to fit eeg data to an ICA model. MNE also applies PCA beforehand to reduce computational load and to avoid overfitting.
    These are the artifacts we will aim to extract ;

    - Jaw Clenching (EMG)
    - Eyes blink
    - Eyes closed
    - Eye movements (different directions)
    - Eyes open (focus onto a point)
    - Deep Breathing (Respiratory Artifacts)
    - Head look left and right (neck muscles)

    In order, using this class will look like this (in this situation, I'll only be using the eye blinking artifact):

    ```python
    >> create("profile_1");

    >> record_blinking_docs([0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8]);
    >> # same as last step until all data collected. It is important to note that the 250hz sample rate should be respected, avoid training with less or more than 250 samples at a time.

    >> export(); # will create `.fif` file from collected data and fit the ICA model
    ```
"""

import time;
from typing import List
import numpy;
import os;
import pandas as pd;
import mne;

CHANNEL_COUNT = 8;
SAMPLE_RATE = 250;

# Global variables
profile_name: str = "";
artifact_names = ["jaw_clench", "eyes_blink", "eyes_closed", "eye_movement", "eyes_open", "deep_breathing", "head_movement"];
columns = ["timestamp"] + [f"ch-{i+1}" for i in range(CHANNEL_COUNT)] + ["artifact"]
eeg_buffer = pd.DataFrame(columns=columns)


# [START DEFINITIONS]

create_docs: str = """
    Creates a new ICA model instance.

    Parameters
    ----------
    profileName : str
        The name of the profile to create. This will also be the name of the exported file.        
        
    Raises
    ------
    FileExistsError
        If a profile with the same name exists, this error will be raised.
""";
def create(profileName: str) -> None:

    if os.path.isfile(f"./models/ica_models/{profileName}.dat"): 
        raise FileExistsError(f"The profile {profileName} already exists");

    global eeg_buffer;
    global profile_name;

    profile_name = profileName;
    eeg_buffer = pd.DataFrame(columns=columns)


create.__doc__ = create_docs;



record_jaw_clench_docs: str = """
    Will add a sample of size ({CHANNEL_COUNT}) to a buffer. When `export()` gets called, the data collected using this method will be saved to a `.fif` file.
    This artifact is of a subject clenching their jaw at every second.

    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    input : List[float] 
        This list has to correspond to the size of CHANNEL COUNT ({CHANNEL_COUNT}). It represents a single sample of EEG data.

    Raises
    ------
    TypeError
        If the type of the input is incorrect in any way this will be thrown, reffer to the messages in the error.
""".format(CHANNEL_COUNT=CHANNEL_COUNT);
def record_jaw_clench(data: List[float]) -> None:
    global eeg_buffer;
    
    if (len(data) != CHANNEL_COUNT):
        raise TypeError("Incorrect Channel Count.");

    timestamp = time.time();
    new_row = pd.DataFrame([[timestamp] + data + ["jaw_clench"]], columns=eeg_buffer.columns);
    eeg_buffer = pd.concat([eeg_buffer, new_row], ignore_index=True);

record_jaw_clench.__doc__ = record_jaw_clench_docs;



record_blinking_docs: str = """
    Will add a sample of size ({CHANNEL_COUNT}) to a buffer. When `export()` gets called, the data collected using this method will be saved to a `.fif` file.
    This artifact is of a subject continuously and rapidly blinking.

    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    input : List[float] 
        This list has to correspond to the size of CHANNEL COUNT ({CHANNEL_COUNT}). It represents a single sample of EEG data.

    Raises
    ------
    TypeError
        If the type of the input is incorrect in any way this will be thrown, reffer to the messages in the error.
""".format(CHANNEL_COUNT=CHANNEL_COUNT);
def record_blinking(data: List[float]) -> None:
    global eeg_buffer;
    
    if (len(data) != CHANNEL_COUNT):
        raise TypeError("Incorrect Channel Count.");

    timestamp = time.time();
    new_row = pd.DataFrame([[timestamp] + data + ["jaw_clench"]], columns=eeg_buffer.columns);
    eeg_buffer = pd.concat([eeg_buffer, new_row], ignore_index=True);
record_blinking.__doc__ = record_blinking_docs;



record_closed_eyes_docs: str = """
    Will add a sample of size ({CHANNEL_COUNT}) to a buffer. When `export()` gets called, the data collected using this method will be saved to a `.fif` file.
    This artifact will simply be of a subject having their eyes closed.
    
    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    input : List[float] 
        This list has to correspond to the size of CHANNEL COUNT ({CHANNEL_COUNT}). It represents a single sample of EEG data.

    Raises
    ------
    TypeError
        If the type of the input is incorrect in any way this will be thrown, reffer to the messages in the error.
""".format(CHANNEL_COUNT=CHANNEL_COUNT);
def record_closed_eyes(data: List[float]) -> None:
    pass;
record_closed_eyes.__doc__ = record_closed_eyes_docs;



record_eye_movement_docs: str = """
    Will add a sample of size ({CHANNEL_COUNT}) to a buffer. When `export()` gets called, the data collected using this method will be saved to a `.fif` file.
    This artifact will have a subject looking in different directions sporadically.
    
    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    input : List[float] 
        This list has to correspond to the size of CHANNEL COUNT ({CHANNEL_COUNT}). It represents a single sample of EEG data.

    Raises
    ------
    TypeError
        If the type of the input is incorrect in any way this will be thrown, reffer to the messages in the error.
""".format(CHANNEL_COUNT=CHANNEL_COUNT);
def record_eye_movement(data: List[float]) -> None:
    pass;
record_eye_movement.__doc__ = record_eye_movement_docs;



record_eyes_open_docs: str = """
    Will add a sample of size ({CHANNEL_COUNT}) to a buffer. When `export()` gets called, the data collected using this method will be saved to a `.fif` file.
    This artifact will be of a subject staring at a cross on the viewport provided.
    
    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    input : List[float] 
        This list has to correspond to the size of CHANNEL COUNT ({CHANNEL_COUNT}). It represents a single sample of EEG data.

    Raises
    ------
    TypeError
        If the type of the input is incorrect in any way this will be thrown, reffer to the messages in the error.
""".format(CHANNEL_COUNT=CHANNEL_COUNT);
def record_eyes_open(data: List[float]) -> None:
    pass;
record_eyes_open.__doc__ = record_eyes_open_docs;



record_deep_breathing_docs: str = """
    Will add a sample of size ({CHANNEL_COUNT}) to a buffer. When `export()` gets called, the data collected using this method will be saved to a `.fif` file.
    This artifact will be of a subject taking deep breaths.
    
    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    input : List[float] 
        This list has to correspond to the size of CHANNEL COUNT ({CHANNEL_COUNT}). It represents a single sample of EEG data.

    Raises
    ------
    TypeError
        If the type of the input is incorrect in any way this will be thrown, reffer to the messages in the error.
""".format(CHANNEL_COUNT=CHANNEL_COUNT);
def record_deep_breathing(data: List[float]) -> None:
    pass;
record_deep_breathing.__doc__ = record_deep_breathing_docs;


record_neck_movements_docs: str = """
    Will add a sample of size ({CHANNEL_COUNT}) to a buffer. When `export()` gets called, the data collected using this method will be saved to a `.fif` file.
    This artifact will be of a subject looking left and then right to record neck muscles.
    
    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    input : List[float] 
        This list has to correspond to the size of CHANNEL COUNT ({CHANNEL_COUNT}). It represents a single sample of EEG data.

    Raises
    ------
    TypeError
        If the type of the input is incorrect in any way this will be thrown, reffer to the messages in the error.
""".format(CHANNEL_COUNT=CHANNEL_COUNT);
def record_neck_movements(data: List[float]) -> None:
    pass;
record_neck_movements.__doc__ = record_neck_movements_docs;



export_docs: str = """
    This method will take all of the recorded data into a file named `./ica_models/artifact_dataset/<PROFILE_NAME>.fif`. All artifacts in this file will 
    be classified. Then, a ICA model will have the corresponding file fitted to it. Then, 

    To start training a model, please use `create(profileName: str) -> None;`.

    Parameters
    ----------
    None
        
    Returns
    ----------
    None
""".format(CHANNEL_COUNT=CHANNEL_COUNT);
def export() -> None:

    global profile;
    global profile_name;
    if profile == None:
        raise FileNotFoundError("No Profile is currently in training. try specifying a profile name.\n");

    profile.eval();

    with torch.inference_mode():
        torch.onnx.export(
            profile,
            torch.randn(1, 1, 8, 250), # (window, in_channel, electrode, sample_size)
            f"./models/{profile_name}",
            export_params=True,
            opset_version=11,
            input_names=["input"],
            output_names=["output"],
            dynamic_axes={'input': {0: 'batch_size'}, 'output': {0: 'batch_size'}} # Allow dynamic batch size
        );
export.__doc__ = export_docs;




# train_docs: str = """
#     Will add a sample of size ({CHANNEL_COUNT}) to the window and then feed the window to the model. When training, pass the stream 

#     To start training a model, please use `create(profileName: str) -> None;`.

#     Parameters
#     ----------
#     input : List[float] 
#         This list has to correspond to the size of CHANNEL COUNT ({CHANNEL_COUNT}). It represents a single sample of EEG data.

#     target : str 
#         This is the corresponding label for the EEG data input. For our project this is {CLASSES}.
        
#     Raises
#     ------
#     TypeError
#         If the type of the input is incorrect in any way this will be thrown, reffer to the messages in the error.
# """.format(CHANNEL_COUNT=CHANNEL_COUNT, CLASSES=", ".join(CLASSES));
# def train(input: List[float], target: str) -> None:

#     if len(input) != CHANNEL_COUNT: raise TypeError(f"\nThe input length is invalid. \nActual Length: {len(input)}\nExpected Length: {CHANNEL_COUNT}");
#     if not all(isinstance(x, (int, float)) for x in input): raise TypeError("\nThe input type is invalid. The elements are not numbers.");

#     global profile, eeg_buffer;

#     new_row = pd.DataFrame([input], columns=[f"electrode_{i+1}" for i in range(CHANNEL_COUNT)]);
#     eeg_buffer = pd.concat([eeg_buffer, new_row], ignore_index=True);

#     if len(eeg_buffer) > WINDOW_LENGHT:
#         eeg_buffer = eeg_buffer.iloc[1:].reset_index(drop=True);

#     # Train only when the buffer reaches 250 samples
#     if len(eeg_buffer) == WINDOW_LENGHT:
    
#         X = torch.tensor(eeg_buffer.values, dtype=torch.float32).unsqueeze(0).unsqueeze(0)  # Shape: (1, 1, 8, 250)
#         y = torch.tensor([CLASSES.index(target)], dtype=torch.long)

#         # Training process
#         criterion = nn.CrossEntropyLoss();
#         optimizer = torch.optim.Adam(profile.parameters(), lr=0.001);

#         profile.train();
#         optimizer.zero_grad();

#         preds = profile(X);
#         loss = criterion(preds, y);

#         loss.backward();
#         optimizer.step();

#         print(f"Training Step: Loss = {loss.item():.4f}");
# train.__doc__ = train_docs;
# # [END DEFINITIONS]
