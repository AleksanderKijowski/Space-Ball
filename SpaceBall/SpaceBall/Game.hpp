#pragma once
#include "stdafx.h"
#include "ExceptionHandlerBuilder.hpp"
#include "GameContext.hpp"

class Game
{
private:
	std::unique_ptr<IExceptionHandler> _exceptionHandler;
	std::shared_ptr<GameContext> _context;

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
	void Update() const
	{
		_context->GetCurrentAppState()->Update();
	}
	
	void Render() const
	{
		_context->GetCurrentAppState()->Render();
		_context->Display();
	}

	void RunGameLoop() const
	{
		_context->PushMainMenuState();

		while (!_context->IsAppEnding())
		{
			_context->UpdateEvents();
			Update();
			Render();
		}
	}
};