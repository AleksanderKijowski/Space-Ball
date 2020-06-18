#pragma once
#include "BuilderState.hpp"
#include "Level.hpp"

class LevelBuilder
{
private:

public:
	LevelBuilder() = default;
	~LevelBuilder() = default;

	int GenerateLevelToFileFromList(List<int> values)
	{
		var generatedLevelsCount = GetConstructedLevelsNumber();

		var path = LevelsCatalogPath + std::to_string(generatedLevelsCount + 1) + ".txt";
		var levelFile = std::ofstream(path);

		if (levelFile.is_open())
		{
			levelFile << GridSizeX << std::endl;
			levelFile << GridSizeY << std::endl;

			for (var y = 0; y < GridSizeY; y++)
			{
				for (var x = 0; x < GridSizeX; x++)
				{
					levelFile << values.front() << " ";
					values.pop_front();
				}

				levelFile << std::endl;
			}
			levelFile.close();

			SetConstructedLevelsCount(generatedLevelsCount + 1);
		}
		else
		{
			throw new FileNotFoundException(path);
		}

		return generatedLevelsCount + 1;
	}

	int GetConstructedLevelsNumber() const
	{
		var generatedLevelsCount = 0;

		var file = std::fstream(BuiltLevelsPath);
		if (file.is_open())
		{
			file >> generatedLevelsCount;
		}
		else
		{
			throw new FileNotFoundException(BuiltLevelsPath);
		}
		file.close();

		return generatedLevelsCount;
	}

	List<string> GetLevelNames()
	{
		var result = List<string>();

		for (var i = 1; i <= GetConstructedLevelsNumber(); i++)
		{
			result.push_back("Level" + std::to_string(i));
		}

		return result;
	}

	std::shared_ptr<Level> GetLevelById(int id)
	{
		var level = new Level();
		var result = std::shared_ptr<Level>(level);
		var path = LevelsCatalogPath + std::to_string(id + 1) + ".txt";
		level->LoadFromFile(path);
		return result;
	}

private:
	void SetConstructedLevelsCount(int count)
	{
		var file = std::fstream(BuiltLevelsPath, std::fstream::in | std::fstream::out | std::fstream::trunc);

		if (file.is_open())
		{
			file << count;
		}
		else
		{
			throw new FileNotFoundException(BuiltLevelsPath);
		}
	}
};