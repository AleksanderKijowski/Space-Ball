#pragma once
#include "stdafx.h"
#include "FileNotFoundException.hpp"

class Level
{
private:
	int sizeX = 0;
	int sizeY = 0;
	List<int> values = List<int>();

public:
	Level() = default;
	Level(Level& level)
	{
		sizeX = level.sizeX;
		sizeY = level.sizeY;
		values = level.values;
	}

	~Level() = default;

	bool LoadFromFile(string path)
	{
		values.clear();
		var file = std::ifstream(path);
		if (file.is_open())
		{
			file >> sizeX;
			file >> sizeY;

			var value = 0;
			for (var y = 0; y < sizeY; y++)
			{
				for (var x = 0; x < sizeX; x++)
				{
					file >> value;
					values.push_back(value);
				}
			}
			file.close();

			return true;
		}
		else
		{
			throw new FileNotFoundException(path);
		}
	}

	int GetSizeX() const
	{
		return sizeX;
	}

	int GetSizeY() const
	{
		return sizeY;
	}

	List<int> GetValues() const
	{
		return values;
	}
};