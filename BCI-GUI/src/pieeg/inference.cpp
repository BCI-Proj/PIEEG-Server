#include "pieeg/inference.h"

void Inference::Create(bool isIca, const wchar_t* profileName)
{
	const wchar_t* command = L"python";
	HINSTANCE result = ShellExecute(NULL, L"open", command, NULL, NULL, SW_SHOWNORMAL);

	if ((int)result <= 32)
	{
		std::cerr << "Failed to execute" << std::endl;
	}
}

void Inference::Train(bool isIca, float* electrodes)
{
	// call TrainEOG, TrainJaw, TrainBreathing
}

void Inference::Export(bool isIca)
{
	try
	{
		//if (isIca)
			// create .dat file called from ica_inference.py
		//else
			// create .onnx file called from inference.py
	}
	catch (const std::exception &e)
	{
		Info(L"Error", L"Cannot create model file", MB_ICONERROR);
	}
}
