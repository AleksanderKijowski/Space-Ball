#include "stdafx.h"
#include "SupportedKeysMapBuilder.h"

Map<string, int>* SupportedKeysMapBuilder::BuildSupportedKeysMap()
{
	var path = SupportedKeysPath;
	var file = std::ifstream(path);
	var result = new Map<string, int>();
	
	if (file.is_open())
	{
		int i = 0;
		string key = "";
		while (file >> key)
		{
			result->emplace(key, i);
			++i;
		}

		if (result->empty())
		{
			throw WrongFileContentException(path);
		}
	}
	else
	{
		delete result;
		throw FileNotFoundException(path);
	}

	file.close();
	
	return result;
}