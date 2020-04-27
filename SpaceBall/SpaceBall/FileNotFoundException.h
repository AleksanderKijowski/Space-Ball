#pragma once
#include "Exception.h"

class FileNotFoundException : public Exception
{
	public:
		FileNotFoundException(string filePath)
			: Exception("File could not be opened. Path was :" + filePath)
		{
		}
};