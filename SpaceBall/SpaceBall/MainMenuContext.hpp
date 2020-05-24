#pragma once
#include "stdafx.h"
#include "MainMenuKeyBindsBuilder.hpp"
#include "GameContextShared.hpp"

class MainMenuContext
{
protected:
	GameContextShared* _context;
	std::shared_ptr<sf::RenderWindow> _window;
	std::shared_ptr<Map<string, int>> _keyBinds;

	MainMenuContext(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window, 
		std::shared_ptr<Map<string, int>> supportedKeys)
	{
		_context = context;
		_window = window;
		_keyBinds.reset(MainMenuKeyBindsBuilder().Build(supportedKeys));
	}
};