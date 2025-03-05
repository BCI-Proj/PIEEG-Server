"""
    This file will be used to load an ICA model

    ```python
    >> load("profile1");

    >> clean([0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8]);

    >> close();

    ```
"""




# [START DEFINITIONS]

from typing import List


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
    pass;

load.__doc__ = load_docs;



clean_docs: str = """
    Takes and cleans given data using the loaded ICA model.

    Parameters
    ----------
    data : List[float]
        The raw data source.
        
    Raises
    ------
""";
def clean(data: List[float]) -> List[float]:
    pass;

clean.__doc__ = clean_docs;



clost_docs: str = """
    Closes the program and lets go of the model from the memory.

    Parameters
    ----------
        
    Raises
    ------
""";
def clean(data: List[float]) -> List[float]:
    pass;

clean.__doc__ = clean_docs;

# [END DEFINITIONS]