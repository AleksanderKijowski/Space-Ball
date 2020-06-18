#pragma once
#include "stdafx.h"
#include "IState.hpp"
#include "RenderWindowBuilder.hpp"
#include "SupportedKeysMapBuilder.hpp"
#include "MainMenuUpdateParams.hpp"
#include "BuilderUpdateParams.hpp"
#include "GameStateUpdateParams.hpp"

class GameContextShared
{
protected:
	const float DelayBeetweenInputsWhenSwitchingStatesInSeconds = 0.5;
	std::shared_ptr<sf::RenderWindow> _window;
	std::unique_ptr<Stack<std::shared_ptr<IState>>> _statesStack;
	std::shared_ptr<Map<string, int>> _supportedKeys;

	bool _appEnding = false;

	sf::Clock _clock;
	float _elapsedTime;
	bool _isReadyToReceiveInput;


	void UpdateAppEnding()
	{
		if (_window == nullptr || !_window->isOpen()) _appEnding = true;
		if (_statesStack == nullptr || _statesStack->empty() || _statesStack->top() == nullptr) _appEnding = true;
	}

public:
	GameContextShared()
	{
		_window.reset(RenderWindowBuilder().BuildRenderWindow());
		_supportedKeys.reset(SupportedKeysMapBuilder().BuildSupportedKeysMap());
		_statesStack.reset(new Stack<std::shared_ptr<IState>>());

		_clock.restart();
		_elapsedTime = 0;
		_isReadyToReceiveInput = false;
	}

	~GameContextShared() = default;

	bool IsAppEnding()
	{
		UpdateAppEnding();
		return _appEnding;
	}

	std::shared_ptr<IState> GetCurrentAppState() const
	{
		return _statesStack->top();
	}

	void UpdateEvents()
	{
		sf::Event eventBuffor;
		while (_window->pollEvent(eventBuffor))
		{
			switch (eventBuffor.type)
			{
			case sf::Event::Closed:
				_window->close();
				break;
			}
		}
	}

	void PopState()
	{
		_statesStack->pop();
		StateChanged();
		UpdateAppEnding();
	}

	void PushNewState(std::shared_ptr<IState> state)
	{
		_statesStack->push(state);
		StateChanged();
	}

	void UpdateClock()
	{
		if (_isReadyToReceiveInput)
		{
			_elapsedTime = _clock.getElapsedTime().asSeconds();
		}
		else
		{
			_elapsedTime += _clock.getElapsedTime().asSeconds();
			if (_elapsedTime > DelayBeetweenInputsWhenSwitchingStatesInSeconds)
			{
				_elapsedTime = 0;
				_isReadyToReceiveInput = true;
			}
		}

		_clock.restart();
	}

	std::shared_ptr<Map<string, int>> GetSupportedKeys() const
	{
		return _supportedKeys;
	}

	MainMenuUpdateParams GetMainMenuUpdateParams() const
	{
		return MainMenuUpdateParams(sf::Mouse::isButtonPressed(sf::Mouse::Left), sf::Mouse::getPosition(*_window));
	}

	BuilderUpdateParams GetBuilderUpdateParams() const
	{
		return BuilderUpdateParams(sf::Mouse::isButtonPressed(sf::Mouse::Left), sf::Mouse::getPosition(*_window));
	}

	GameStateUpdateParams GetGameStateUpdateParams() const
	{
		return GameStateUpdateParams(_elapsedTime);
	}

protected:
	virtual void StateChanged()
	{
	}
};