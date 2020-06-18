#pragma once
#include "IOption.hpp"
#include "ArgumentOutOfRangeException.hpp"

enum MessageBoxOption
{
	zero,
	first,
	second,
};

class MessageBoxOptions : public IOption
{
private:
	MessageBoxOption Option;

public:
	virtual void SetValue(int value)
	{
		Value = value;

		switch (value)
		{
		case 0:
			Option = zero;
			break;

		case 1:
			Option = first;
			break;

		case 2:
			Option = second;
			break;

		default:
			throw  new ArgumentOutOfRangeException("MessageBoxOptions for value: " + std::to_string(value));
		}
	}

	MessageBoxOption Get() const
	{
		return Option;
	}

	void Reset()
	{
		SetValue(0);
	}
};