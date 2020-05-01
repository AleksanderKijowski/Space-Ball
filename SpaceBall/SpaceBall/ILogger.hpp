#pragma once
#include "stdafx.h"

class ILogger
{
protected:
	bool _isInitialized;
	
public:
	virtual void Log(List<string> text) abstract;
	
	bool GetIsInitialized() const
	{
		return _isInitialized;
	}
};