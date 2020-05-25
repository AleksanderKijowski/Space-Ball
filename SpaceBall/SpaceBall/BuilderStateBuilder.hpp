#pragma once
#include "BuilderState.hpp"

static class BuilderStateBuilder
{
public:
	BuilderStateBuilder() = default;
	std::shared_ptr<BuilderState> Build(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
	{
		var state = new BuilderState(context, window, supportedKeys);

		return std::shared_ptr<BuilderState>(state);
	}
};