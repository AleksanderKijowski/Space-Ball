#pragma once
#include "stdafx.h"
#include "ILogger.hpp"
#include "DateTimeProvider.hpp"

class Logger : public ILogger
{
public:
	Logger()
	{
		_isInitialized = true;
		Initialize();
	}
	
	~Logger() = default;

	virtual void Log(List<string> text)
	{
		var path = ExceptionSavingDirectoryPath + "/" + DateTime().Now().ToString() + ".txt";
		var file = std::ofstream(path, std::ios::out);
		
		if (file.is_open())
		{
			for (var line : text)
			{
				file << line << std::endl;
			}
			
			file.close();
		}
		else
		{
			std::cerr << "Exception directory could not be opened. Path was : " << path << std::endl;
		}
	}

private:
	void Initialize()
	{
		var path = ExceptionSavingDirectoryPath + "/test.txt";
		var file = std::ofstream(path);

		if (file.is_open())
		{
			file << "Test data";
		}
		else
		{
			std::cerr << "Exception directory not initialized. Path was : " << path << std::endl;
			_isInitialized = false;
		}

		file.close();
		if (remove(path.c_str()) != 0)
		{
			std::cerr << "Deleting file failed. Path was : " << path << std::endl;
			_isInitialized = false;
		}
	}
};