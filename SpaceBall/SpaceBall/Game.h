#pragma once
#include "RenderWindowBuilder.h"

class Game
{
	private:
		std::unique_ptr<sf::RenderWindow> _window;
	
	public: 
		Game();
		virtual ~Game();
	
		void Run();
	
	private:
};

