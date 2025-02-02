# Inference for Sema-Cerebrum

---

In the C++ code used in our project, we will call the `./inference.py` program to make inferences. Different commands will be available and this document will detail how to use this file/tool.

### Installing and adding dependencies

---

To install necessary requirements, I like to place a python virtual environment at the root of the project.

```bash
python -m venv venv
```

you can then activate the environment by using either command specific to your platform :

```bash
venv/Scripts/activate # windows

# or

source /venv/bin/activate # macos
```

To then install dependencies, you can run this command :

```bash
pip install -r requirements.txt
```

Then, let's say you add requirements, please run : `pip freeze > requirements.txt`
