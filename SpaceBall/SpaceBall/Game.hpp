#pragma once
#include "stdafx.h"
#include "RenderWindowBuilder.hpp"
#include "ExceptionHandlerBuilder.hpp"
#include "SupportedKeysMapBuilder.hpp"

class Game
{
private:
	std::unique_ptr<IExceptionHandler> _exceptionHandler;
	std::unique_ptr<sf::RenderWindow> _window;
	std::unique_ptr<Map<string, int>> _supportedKeys;

	sf::Event _event;

public:
	Game()
	{
		_exceptionHandler.reset(ExceptionHandlerBuilder().BuildExceptionHandler());
		_window.reset(RenderWindowBuilder().BuildRenderWindow());
		_supportedKeys.reset(SupportedKeysMapBuilder().BuildSupportedKeysMap());
	}
	virtual ~Game() = default;

	void Run()
	{
		if (_exceptionHandler != nullptr)
		{
			RunGameLoop();
		}
	}

private:
	void UpdateEvents()
	{
		while (_window->pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
			{
				_window->close();
			}
		}
	}
	
	void Update()
	{
		
	}
	
	void Render()
	{
		_window->clear();
		_window->display();
	}

	void RunGameLoop()
	{
		try
		{
			while (_window->isOpen())
			{
				UpdateEvents();
				Update();
				Render();
			}
		}
		catch (Exception* exception)
		{
			_exceptionHandler->HandleException(exception);
		}
	}
};