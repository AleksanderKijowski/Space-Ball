#pragma once
#include "IOption.hpp"
#include "ArgumentOutOfRangeException.hpp"

enum BuilderButtonSelectionOption
{
	notSelected,
};

class BuilderButtonSelectionOptions : public IOption
{
private:
	BuilderButtonSelectionOption Option;

public:
	virtual void SetValue(int value)
	{
		Value = value;

		switch (value)
		{
		case 0:
			Option = notSelected;
			break;

		default:
			throw  new ArgumentOutOfRangeException("BuilderButtonSelectionOptions for value: " + std::to_string(value));
		}
	}

	BuilderButtonSelectionOption Get() const
	{
		return Option;
	}

	void Reset()
	{
		SetValue(0);
	}
};