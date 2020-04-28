#pragma once
#include "stdafx.h"
#include "ExceptionHandlerBuilder.hpp"
#include "GameContext.hpp"

class Game
{
private:
	std::unique_ptr<IExceptionHandler> _exceptionHandler;
	std::unique_ptr<GameContext> _context;
	sf::Event _event;

public:
	Game()
	{
		_exceptionHandler.reset(ExceptionHandlerBuilder().BuildExceptionHandler());
	}
	
	virtual ~Game() = default;

	void Run()
	{
		if (_exceptionHandler != nullptr)
		{
			try
			{
				_context.reset(new GameContext());

				RunGameLoop();
			}
			catch(Exception* exception)
			{
				_exceptionHandler->HandleException(exception);
			}
		}
	}

private:
	void Update()
	{
		_context->GetCurrentAppState()->Update();
	}
	
	void Render()
	{
		_context->GetCurrentAppState()->Render();
	}

	void RunGameLoop()
	{
		while (!_context->IsAppEnding())
		{
			_context->UpdateEvents();
			Update();
			Render();
		}
	}
};