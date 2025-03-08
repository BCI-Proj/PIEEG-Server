#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "globals.h"
#include "window/menu.h"

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
	inline std::unordered_map<Menu::TrainingDirection, const char*> trainDirectionMap =
	{
		{Menu::kLeft,    "left"},
		{Menu::kRight,   "right"},
		{Menu::kTop ,    "up"},
		{Menu::kBottom , "down"},
		{Menu::kCenter , "baseline"},
	};

	inline const std::string baseCommand = "python ./inference/inference.py ";

	// If ICA, create .dat file called from ica_inference.py else create .onnx from inference.py
	void Create (const char* profileName);

	// If ICA, call Training functions for Jaw, EOG, Breathing else train 
	void Train  (const char* profileName, const float* electrodes, Menu::TrainingDirection direction);

	// If ICA, export .dat, else export .onnx
	void Export (const char* profileName); 
}