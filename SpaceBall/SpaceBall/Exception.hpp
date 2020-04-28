#pragma once
#include "stdafx.h"

class Exception : public std::exception
{
private:
	string _message;

public:
	Exception(string message)
	{
		_message = message;
	}

	virtual string ToString()
	{
		return _message;
	}

	virtual List<string> GetLogMessage()
	{
		var result = List<string>();
		result.push_back(ToString());

		return result;
	}
};