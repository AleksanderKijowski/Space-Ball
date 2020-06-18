#pragma once
#include "IOption.hpp"

class CounterPort : IOption
{
public:
	CounterPort()
	{
		Value = -1;
	}

	void SetValue(int value)
	{
		Value = value;
	}

	int GetValue() const
	{
		return Value;
	}
};