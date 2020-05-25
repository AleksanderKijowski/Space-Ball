#pragma once
#include "IState.hpp"
#include "BuilderContext.hpp"


class BuilderState : public IState, public BuilderContext
{
public:
	BuilderState(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
		: IState(), BuilderContext(context, window, supportedKeys)
	{
	}

	virtual void Update() override
	{
		var params = _context->GetBuilderUpdateParams();

		_tileSelection->Update(params.MouseCoordinates, params.MouseClicked);
	}

	virtual void Render() override
	{
		_tileSelection->Render(_window);
	}
};
