#pragma once
#include "stdafx.h"
#include "KeyBindsBuilder.hpp"
#include "GameContextShared.hpp"
#include "MainMenuButtonList.hpp"
#include "MainMenuOptions.hpp"

class MainMenuContext
{
protected:
	GameContextShared* _context;
	std::shared_ptr<sf::RenderWindow> _window;
	std::shared_ptr<Map<string, int>> _keyBinds;
	std::shared_ptr<MainMenuButtonList> _buttonList;

	std::shared_ptr<MainMenuOptions> _port;

	MainMenuContext(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window, 
		std::shared_ptr<Map<string, int>> supportedKeys)
	{
		_context = context;
		_window = window;
		_port.reset(new MainMenuOptions());
		_keyBinds.reset(KeyBindsBuilder().Build(supportedKeys, MainMenuKeyBindsPath));
		_buttonList.reset(new MainMenuButtonList(sf::Vector2f(_window->getSize()), _port));
	}
};