#pragma once
#include "FileNotFoundException.hpp"

class KeyBindsBuilder
{
public:
	KeyBindsBuilder() = default;

	Map<string, int>* Build(std::shared_ptr<Map<string, int>> supportedKeys, const string path)
	{
		var file = std::ifstream(path);
		if (file.is_open())
		{
			var result = new Map<string, int>();
			var option = string();
			var value = string();

			while (file >> option >> value)
			{
				result->emplace(option, supportedKeys->at(value));
			}

			return result;
		}
		else
		{
			throw new FileNotFoundException(path);
		}
	}
};