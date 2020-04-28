#pragma once
#include "stdafx.h"
#include "Exception.hpp"

class FileNotFoundException : public Exception
{
public:
	FileNotFoundException(string filePath)
		: Exception("File could not be opened. Path was :" + filePath)
	{
	}
};