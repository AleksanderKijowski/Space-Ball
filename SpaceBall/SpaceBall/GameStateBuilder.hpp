#pragma once
#include "GameState.hpp"

static class GameStateBuilder
{
public:
	GameStateBuilder() = default;
	std::shared_ptr<GameState> Build(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys,
		std::shared_ptr<Level> level)
	{
		var state = new GameState(context, window, supportedKeys, level);

		return std::shared_ptr<GameState>(state);
	}
};