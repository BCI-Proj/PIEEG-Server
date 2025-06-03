# Sema Cerebrum
This is the app that will receive and interpret the eeg data from the client (PiEEG). The goal is to make controls on an interface using nothing but your brain signals.

## Flow
The app will **receive** eeg data from the PiEEG through an outlet opened on the PiEEG from MNE_LSL. MNE_LSL lets us scale to other sensors later and also timestamps all of our data. 
Then, the data should be **cleaned**. There are different methods to clean artifacts from EEGs one of them being ICA. MNE offers an implementation of ICA as well as artifact identification methods but only in an offline paradigm. There is research being done on online ICA implementations for real-time noise removal applications like ORICA(Online Recursive Idenpendant Component Analysis) but this isn't a feature yet available in MNE. 
Then, there will be two different steps for using our app, training and actual use. **Training** will be split in two non-equal parts. One will be to record artifact data to fit to an ICA model and another to train an EEGNet or other model for **Inference** on difference controls of the app. 


## Libraries
- MNE_LSL
- Pytorch
- DearPyGui

## How to build
To determine

## How to run
To Determine

### From a Release
To Determine

## Logging View
To Determine

## Training View
To Determine

## Plotting View
To Determine

## Videos
[SEMA-CEREBRUM 0.1.0 – YOUTUBE](https://youtu.be/Nd4Kb7TSLpA)

SEMA-CEREBRUM 1.0.0 – W.I.P










 
