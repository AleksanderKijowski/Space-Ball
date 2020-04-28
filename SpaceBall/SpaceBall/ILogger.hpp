#pragma once
#include "stdafx.h"

class ILogger
{
protected:
	bool _isInitialized;
	
public:
	virtual void Log(List<string> text) = 0;
	
	bool GetIsInitialized() const
	{
		return _isInitialized;
	}
};