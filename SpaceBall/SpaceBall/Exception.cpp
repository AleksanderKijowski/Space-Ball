#include "stdafx.h"
#include "Exception.h"

Exception::Exception(string message)
	: std::exception()
{
	_message = message;
}

string Exception::ToString()
{
	return _message;
}