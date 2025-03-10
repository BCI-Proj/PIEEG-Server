#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "globals.h"
#include "window/menu.h"

/// <summary>
/// Namespace that contain methods to make Inference to Python Code
/// </summary>
namespace Inference
{
	/// <summary>
	/// TrainingDirection mapped in string send corresponding strings to Python Program
	/// </summary>
	inline std::unordered_map<Menu::TrainingDirection, const std::string> trainDirectionMap =
	{
		{Menu::kLeft,    "left"},
		{Menu::kRight,   "right"},
		{Menu::kTop ,    "up"},
		{Menu::kBottom , "down"},
		{Menu::kCenter , "baseline"},
	};

	inline const std::string baseCommand = "python ./inference/inference.py ";

	/// <summary>
	/// If ICA, create .dat file called from ica_inference.py else create .onnx from inference.py
	/// </summary>
	/// <param name="profileName">The name of profile that is being trained</param>
	void Create (const char* profileName);

	
	/// <summary>
	/// If ICA, call Training functions for Jaw, EOG, Breathing else train
	/// </summary>
	/// <param name="profileName">The name of profile that is being trained</param>
	/// <param name="electrodes">Float ptr of values coming from the electrodes</param>
	/// <param name="direction">The TrainingDirection </param>
	void Train  (const char* profileName, const float* electrodes, Menu::TrainingDirection direction);

	/// <summary>
	/// If ICA, export the model to .dat else to .onnx
	/// </summary>
	/// <param name="profileName">The name of profile that is being trained</param>
	void Export (const char* profileName); 
}