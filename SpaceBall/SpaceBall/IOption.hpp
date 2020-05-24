#pragma once
#include "stdafx.h"

class IOption
{
protected:
	int Value = 0;

public:
	IOption() = default;
	
	virtual void SetValue(int value) abstract;
};

class OptionValueObject
{
private:
	std::shared_ptr<IOption> Option;
	int Value;

public:
	OptionValueObject(std::shared_ptr<IOption> option, int value)
	{
		Option = option;
		Value = value;
	}

	void SetValue()
	{
		Option->SetValue(Value);
	}
};