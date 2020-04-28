#pragma once
#include "stdafx.h"
#include"ExceptionHandler.hpp"

class ExceptionHandlerBuilder
{
public:
	ExceptionHandlerBuilder() = default;
	
	ExceptionHandler* BuildExceptionHandler()
	{
		var result = new ExceptionHandler();

		if (!result->IsInitialized())
		{
			delete result;
			result = nullptr;
		}

		return result;
	}
};