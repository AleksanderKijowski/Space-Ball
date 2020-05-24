#pragma once
#include "IState.hpp"
#include "MainMenuContext.hpp"

class MainMenuState : public IState, public MainMenuContext
{
private:

public:
	MainMenuState(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
		: IState(), MainMenuContext(context, window, supportedKeys)
	{

	}

	virtual void Update() override
	{
		var params = _context->GetMainMenuUpdateParams();

		for (var key = _keyBinds->begin(); key != _keyBinds->end(); key++)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key->second)))
			{
				HandleToPort(key);
			}
		}
	}

	virtual void Render() override
	{

	}

private:
	void HandleToPort(Map<string, int>::iterator key)
	{
		if (key->first == "Exit")
		{
			ExitKeyPressed();
		}
	}

	void ExitKeyPressed()
	{

	}
};