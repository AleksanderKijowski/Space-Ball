#pragma once
#include "IState.hpp"
#include "MainMenuContext.hpp"
#include "Button.hpp"

class MainMenuState : public IState, public MainMenuContext
{
private:
	Button* button;
	sf::Color* normal;
	sf::Color* hover;
	sf::Color* clicked;

public:
	MainMenuState(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
		: IState(), MainMenuContext(context, window, supportedKeys)
	{
		normal = new sf::Color(sf::Color::Blue);
		hover = new sf::Color(sf::Color::Green);
		clicked = new sf::Color(sf::Color::Cyan);

		var params = ButtonParams();
		params.Size = sf::Vector2f(100, 100);
		params.Position = sf::Vector2f(100, 100);
		params.NormalColor = normal;
		params.HoverColor = hover;
		params.ClickedColor = clicked;

		button = new Button(params);
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

		button->Update(params.MouseCoordinates, params.MouseClicked);
	}

	virtual void Render() override
	{
		button->Render(_window);
	}

private:
	void HandleToPort(Map<string, int>::iterator key)
	{
		if (key->first == "EXIT")
		{
			ExitKeyPressed();
		}
	}

	void ExitKeyPressed()
	{
		_window->close();
	}
};