#pragma once
#include "IState.hpp"
#include "LevelSelectionContext.hpp"
#include "GameStateBuilder.hpp"

class LevelSelectionState : public IState, public LevelSelectionContext
{
public:
	LevelSelectionState(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
		: LevelSelectionContext(context, window, supportedKeys)
	{
	}

	virtual void Update()
	{
		UpdateKeys();
		var params = _context->GetBuilderUpdateParams();

		_counter->Update(params.MouseCoordinates, params.MouseClicked);

		if (_port->GetValue() != -1)
		{
			var level = LevelBuilder().GetLevelById(_port->GetValue());
			_port->SetValue(-1);

			_context->PushNewState(GameStateBuilder().Build(
				_context,
				_window,
				_context->GetSupportedKeys(),
				level));
		}
	}

	virtual void Render()
	{
		_counter->Render(_window);
	}

private:
	void HandleToPort(Map<string, int>::iterator key)
	{
		if (key->first == "EXIT")
		{
			BackKeyPressed();
		}
	}

	void BackKeyPressed()
	{
		_context->PopState();
	}

	void UpdateKeys()
	{
		for (var key = _keyBinds->begin(); key != _keyBinds->end(); key++)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key->second)))
			{
				HandleToPort(key);
			}
		}
	}
};