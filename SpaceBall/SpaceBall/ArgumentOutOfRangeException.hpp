#pragma once
#include "Exception.hpp"

class ArgumentOutOfRangeException : public Exception
{
public:
	ArgumentOutOfRangeException(string codeLocation)
		: Exception("Argument not found as a key in switch in: " + codeLocation)
	{	
	}
};