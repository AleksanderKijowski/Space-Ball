#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	_window.reset(RenderWindowBuilder().BuildRenderWindow());
	_supportedKeys.reset(SupportedKeysMapBuilder().BuildSupportedKeysMap());
}

Game::~Game()
{
}

void Game::Run()
{
	while (_window->isOpen())
	{
		UpdateEvents();
		Update();
		Render();
	}
}

void Game::UpdateEvents()
{
	while (_window->pollEvent(_event))
	{
		if (_event.type == sf::Event::Closed)
		{
			_window->close();
		}
	}
}


void Game::Update()
{
	
}

void Game::Render()
{
	_window->clear();
	_window->display();
}