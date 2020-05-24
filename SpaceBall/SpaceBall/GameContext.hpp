#pragma once
#include "GameContextShared.hpp"
#include "MainMenuStateBuilder.hpp"

class GameContext : public GameContextShared
{
public:
	void PushMainMenuState()
	{
		PushNewState(MainMenuStateBuilder().Build(this, _window, _supportedKeys));
	}

	void Display()
	{
		_window->display();
	}
};