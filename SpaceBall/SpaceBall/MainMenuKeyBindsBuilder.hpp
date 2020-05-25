#pragma once
#include "FileNotFoundException.hpp"

class MainMenuKeyBindsBuilder
{
public:
	MainMenuKeyBindsBuilder() = default;
	Map<string, int>* Build(std::shared_ptr<Map<string, int>> supportedKeys)
	{
		var path = MainMenuKeyBindsPath;
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