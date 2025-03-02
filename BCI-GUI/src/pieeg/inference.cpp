#include "inference.h"

void Inference::Create(bool isIca, const wchar_t* profileName)
{
	try
	{
		//if (isIca)
		    // create .dat file called from ica_inference.py
		//else
			// create .onnx file called from inference.py
	}
	catch (const std::exception&)
	{
		Info(L"Error", L"Cannot create model file", MB_ICONERROR);
	}
}
 
void Inference::Train(bool isIca, float* electrodes)
{
	// call TrainEOG, TrainJaw, TrainBreathing
}

void Inference::Export(bool isIca)
{
}
