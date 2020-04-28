#pragma once
#include "stdafx.h"
#include "FileNotFoundException.hpp"
#include "WrongFileContentException.hpp"

class SupportedKeysMapBuilder
{
public:
	SupportedKeysMapBuilder() = default;

	static Map<string, int>* BuildSupportedKeysMap()
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
				throw new WrongFileContentException(path);
			}
		}
		else
		{
			delete result;
			throw new FileNotFoundException(path);
		}

		file.close();

		return result;
	}
};