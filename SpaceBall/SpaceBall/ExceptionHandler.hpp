#pragma once
#include "stdafx.h"
#include "IExceptionHandler.hpp"
#include "Exception.hpp"

class ExceptionHandler : public IExceptionHandler
{
private:
	bool _isInitialized;

public:
	ExceptionHandler()
	{
		_isInitialized = true;
		CheckOutputDirectoryAccess();
	};

	void HandleException(Exception* exception) override
	{
		
	}
	
	bool IsInitialized() const
	{
		return _isInitialized;
	}

private:
	void CheckOutputDirectoryAccess()
	{
		var path = ExceptionSavingDirectoryPath + "/test.txt";
		var file = std::ofstream(path);

		if (file.is_open())
		{
			file << "Test data";
		}
		else
		{
			std::cerr << "Exception directory not initialized. Path was: " << path << std::endl;
			_isInitialized = false;
		}

		file.close();
		if (remove(path.c_str()) != 0)
		{
			std::cerr << "Deleting file failed. Path was: " << path << std::endl;
			_isInitialized = false;
		}
	}
};