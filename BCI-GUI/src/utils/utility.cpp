#include "utils/utility.h"

#ifdef _DEBUG
	#include <iostream>
#endif 

void Utility::SaveToJson(const std::string &pathToJson)
{
	std::fstream file;
	file.open(pathToJson, std::ios::out);

	file << document;

#ifdef _DEBUG
	std::cout << "JSON File Has been saved";
#endif
}
