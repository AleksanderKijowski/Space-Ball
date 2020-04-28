#pragma once
#include "stdafx.h"
#include "IState.hpp"

class GameContext
{
private:
	std::shared_ptr<sf::RenderWindow> _window;
	std::unique_ptr<Stack<std::shared_ptr<IState>>> _statesStack;
	std::shared_ptr<Map<string, int>> _supportedKeys;

	bool _appEnding = false;


	void UpdateAppEnding()
	{
		if (_window == nullptr || !_window->isOpen()) _appEnding = true;
		if (_statesStack == nullptr || _statesStack->empty() || _statesStack->top() == nullptr) _appEnding = true;
	}

public:
	GameContext()
	{
		_window.reset(RenderWindowBuilder().BuildRenderWindow());
		_supportedKeys.reset(SupportedKeysMapBuilder().BuildSupportedKeysMap());
	}
	
	~GameContext() = default;

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
		sf::Event eventBuffer;
		while (_window->pollEvent(eventBuffer))
		{
			if (eventBuffer.type == sf::Event::Closed)
			{
				_window->close();
			}
		}
	}
};