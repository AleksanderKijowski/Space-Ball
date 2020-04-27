#pragma once

#include "Exception.h"

class WrongFileContentException : public Exception
{
public:
	WrongFileContentException(string filePath)
		: Exception("File has wrong content. Path was :" + filePath)
	{
	}
};
