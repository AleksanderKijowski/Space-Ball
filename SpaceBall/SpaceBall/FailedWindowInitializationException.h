#pragma once
#include "stdafx.h"
#include "Exception.h"

class FailedWindowInitializationFailedException : public Exception
{
	public:
		FailedWindowInitializationFailedException()
			: Exception("Window initialization failed. Unknown reason.")
		{
		}
};