#pragma once
#include "IOption.hpp"

class BuilderButtonGridOption : public IOption
{
private:

public:
	virtual void SetValue(int value)
	{
		Value = value;
	}

	int Get() const
	{
		return Value;
	}

	void Reset()
	{
		SetValue(0);
	}
};