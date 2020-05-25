#pragma once
#include "stdafx.h"
#include "GameContextShared.hpp"
#include "KeybindsBuilder.hpp"
#include "BuilderButtonSelectionList.hpp"
#include "BuilderButtonSelectionOptions.hpp"

class BuilderContext
{
protected:
	GameContextShared* _context;
	std::shared_ptr<sf::RenderWindow> _window;
	std::shared_ptr<Map<string, int>> _keyBinds;
	std::shared_ptr<BuilderButtonSelectionList> _tileSelection;
	std::shared_ptr<BuilderButtonSelectionOptions> _port;

	BuilderContext(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
	{
		_context = context;
		_window = window;
		_keyBinds.reset(KeyBindsBuilder().Build(supportedKeys, BuilderKeyBindsPath));
		_port.reset(new BuilderButtonSelectionOptions());
		_tileSelection.reset(new BuilderButtonSelectionList(sf::Vector2f(_window->getSize()), _port));
	}
};