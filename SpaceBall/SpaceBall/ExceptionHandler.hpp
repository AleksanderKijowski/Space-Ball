#pragma once
#include "stdafx.h"
#include "IExceptionHandler.hpp"
#include "Logger.hpp"
#include "Exception.hpp"

class ExceptionHandler : public IExceptionHandler
{
public:
	ExceptionHandler()
		: IExceptionHandler(new Logger())
	{
	};

	void HandleException(Exception* exception) override
	{
		if (exception != nullptr)
		{
			_logger->Log(exception->GetLogMessage());
			delete exception;
			std::cerr << "Exception occured. See logs to for details." << std::endl;
		}
	}
	
	bool IsInitialized() const
	{
		return _logger->GetIsInitialized();
	}
};