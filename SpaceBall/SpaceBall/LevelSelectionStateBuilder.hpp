#pragma once
#include "LevelSelectionState.hpp"

static class LevelSelectionStateBuilder
{
public:
	LevelSelectionStateBuilder() = default;
	std::shared_ptr<LevelSelectionState> Build(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
	{
		var state = new LevelSelectionState(context, window, supportedKeys);

		return std::shared_ptr<LevelSelectionState>(state);
	}
};