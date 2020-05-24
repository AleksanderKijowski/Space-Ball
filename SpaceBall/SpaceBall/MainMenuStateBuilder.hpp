#pragma once
#include "MainMenuState.hpp"

static class MainMenuStateBuilder
{
public:
	MainMenuStateBuilder() = default;
	std::shared_ptr<MainMenuState> Build(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
	{
		var state = new MainMenuState(context, window, supportedKeys);

		return std::shared_ptr<MainMenuState>(state);
	}
};