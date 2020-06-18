#pragma once
#include "IOption.hpp"
#include "ArgumentOutOfRangeException.hpp"

enum BuilderButtonSelectionOption
{
	notSelected,
	blueTile,
	yellowTile,
	brick,
	tile,
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

			case 1:
				Option = blueTile;
				break;

			case 2:
				Option = yellowTile;
				break;

			case 3:
				Option = brick;
				break;

			case 4:
				Option = tile;
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