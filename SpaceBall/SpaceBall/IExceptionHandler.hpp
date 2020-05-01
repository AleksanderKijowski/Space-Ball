#pragma once
#include "stdafx.h"
#include "ILogger.hpp"
#include "Exception.hpp"

class IExceptionHandler
{
protected:
	std::unique_ptr<ILogger> _logger;
	
public:
	virtual void HandleException(Exception* exception) abstract;

protected:
	IExceptionHandler(ILogger* logger)
	{
		_logger.reset(logger);
	}
};
