#pragma once

#include <iostream>
#include <Windows.h>
#include "globals.h"

/*
ica_model.py
create <PROFILE_NAME>
record_blinking <DATA>
record_closed_eyes <DATA>
record_eye_movement <DATA>
record_eyes_open <DATA>
export


ica_model_inference.py
load <PROFILE_NAME>
clean <DATA> // returns [SIZE] cleaned data

inference.py
create <PROFILE_NAME>
train <DATA>
export
*/


namespace Inference
{
	// If ICA, create .dat file called from ica_inference.py else create .onnx from inference.py
	void Create (bool isIca, const wchar_t* profileName);

	// If ICA, call Training functions for Jaw, EOG, Breathing else train 
	void Train  (bool isIca, float* electrodes);

	// If ICA, export .dat, else export .onnx
	void Export (bool isIca); 
}