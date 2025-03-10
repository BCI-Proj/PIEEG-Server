#pragma once

#include <string>
#include <fstream>
#include <array>
#include "json.hpp"

namespace Utility
{
	using json = nlohmann::json;

	// Save to json
	inline json document;

	struct Line
	{
		const std::string		name;
		std::array<float, 250>  values;
	};

	struct Chunk
	{
		int						id;
		std::array<Line, 8>		lines;
	};

	void SaveToJson(const std::string &pathToJson);
}