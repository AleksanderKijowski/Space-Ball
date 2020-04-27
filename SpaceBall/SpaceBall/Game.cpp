#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	_window.reset(RenderWindowBuilder().BuildRenderWindow());
}

Game::~Game()
{
}

void Game::Run()
{
}
