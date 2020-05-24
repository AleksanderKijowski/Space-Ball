#pragma once
#include "IOption.hpp"

enum MainMenuOption
{
	unset,
	newGame,
	build,
	settings,
	exitState,
};

class MainMenuOptions : public IOption
{
private:
	MainMenuOption Option;

public:
	virtual void SetValue(int value)
	{
		Value = value;

		switch (value)
		{
			case 0:
				Option = unset;
				break;

			case 1:
				Option = newGame;
				break;

			case 2:
				Option = build;
				break;

			case 3:
				Option = settings;
				break;

			case 4:
				Option = exitState;
				break;

			default:
				// ToDo: Add new exception
				break;
		}
	}

	MainMenuOption Get() const
	{
		return Option;
	}

	void Reset()
	{
		SetValue(0);
	}
};