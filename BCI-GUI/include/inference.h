#pragma once

#include "pybind11/embed.h"

namespace Py = pybind11;
namespace Inference
{
	// If ICA, create .dat file called from ica_inference.py else create .onnx from inference.py
	void Create (bool isIca, const char* profileName);

	// If ICA, call Training functions for Jaw, EOG, Breathing else train 
	void Train  (bool isIca, float electrodes[8]);

	/// If ICA, export .dat, else export .onnx
	void Export (bool isIca); 
}