This will hold the datasets of the artifacts as `FIF` files.

We record artifacts, then fit an ICA model to that dataset.

Naming convention will be `<PROFILE_NAME>-<CURRENT_EPOCH_TIME>.fif` for datasets, and one directory down (`./BCI-GUI/inference/ica_models/`), the model naming convention will be the same as pytorch models : `<PROFILE_NAME>.dat`.