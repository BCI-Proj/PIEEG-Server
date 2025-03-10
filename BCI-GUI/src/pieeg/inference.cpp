#include "pieeg/inference.h"

void Inference::Create(const char* profileName)
{
	std::string createCommand = baseCommand + "create " + profileName;
	int result = system(createCommand.c_str());
	
	if (result)
		Info(L"Cannot create model with profile", L"ERROR", MB_ICONERROR);
}

void Inference::Train(const char* profileName, const float* electrodes, Menu::TrainingDirection direction)
{
	std::string trainCommand = baseCommand + "train " + profileName + " ";

	for (int i = 0; i < Globals::kNumElectrodes; i++)
	{
		trainCommand += std::to_string(electrodes[i]);
		trainCommand += " ";
	}
	trainCommand += trainDirectionMap[direction];

	int result = system(trainCommand.c_str());
	
	if (result)
		Info(L"Cannot send system commands to python file", L"ERROR", MB_ICONERROR);
}

void Inference::Export(const char* profileName)
{
	// need to have onnx dep
	std::string exportCommand = baseCommand + "export " + profileName;
	int result = system(exportCommand.c_str());
	
	if (result) 
		Info(L"Cannot create model file", L"ERROR", MB_ICONERROR);
}
