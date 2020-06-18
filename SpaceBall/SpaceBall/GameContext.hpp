#pragma once
#include "GameContextShared.hpp"
#include "MainMenuStateBuilder.hpp"

class GameContext : public GameContextShared
{
private:
	std::shared_ptr<sf::Texture> _backgroundTexture;
	std::shared_ptr<sf::Sprite> _background;

public:
	GameContext()
	{
		_backgroundTexture.reset(new sf::Texture());

		if (_backgroundTexture->loadFromFile(BackgroundPath))
		{
			_background.reset(new sf::Sprite(*_backgroundTexture));
			_background->setScale(ScaleProvider::Get(sf::Vector2f(_window->getSize())));
		}
		else
		{
			throw new FileNotFoundException(BackgroundPath);
		}
	}

	void PushMainMenuState()
	{
		PushNewState(MainMenuStateBuilder().Build(this, _window, _supportedKeys));
	}

	void Display()
	{
		_window->display();
	}

	void ClearWindow()
	{
		var color = sf::Color(sf::Color::White);
		_window->clear(color);
	}

	void RenderBackground()
	{
		_window->draw(*_background);
	}

	bool CanReveiveInput()
	{
		return _isReadyToReceiveInput;
	}

protected:
	virtual void StateChanged() override
	{
		_isReadyToReceiveInput = false;
	}
};