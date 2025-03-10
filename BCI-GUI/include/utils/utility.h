#pragma once

#include <string>
#include <fstream>
#include <array>
#include "json.hpp"
#include "globals.h"

namespace Utility
{
	using json = nlohmann::json;

	// Save to json
	inline json document;

	/// <summary>
	/// Line that contain 250 floats values that came from PIEEG
	/// </summary>
	struct Line
	{
		const std::string		name;
		std::array<float, 250>  values;
	};

	/// <summary>
	/// Chunk of data that contain lines
	/// </summary>
	struct Chunk
	{
		int	id;
		std::array<Line, Globals::kNumElectrodes> lines;
	};

	/// <summary>
	/// Save all the gathered data to a json file and then use it to
	/// save all the data to a JSON file call export function in python to create a .onnx file
	/// </summary>
	/// <param name="pathToJson"></param>
	void SaveToJson(const std::string &pathToJson);
}