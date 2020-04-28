#pragma once
#include "stdafx.h"
#include "Exception.hpp"

class IExceptionHandler
{
public:
	virtual void HandleException(Exception* exception) = 0;
};
