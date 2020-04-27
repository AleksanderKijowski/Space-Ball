#pragma once
#include "RenderWindowBuilder.h"
#include "SupportedKeysMapBuilder.h"

class Game
{
	private:
		std::unique_ptr<sf::RenderWindow> _window;
		std::unique_ptr<Map<string, int>> _supportedKeys;

		sf::Event _event;
	
	public: 
		Game();
		virtual ~Game();
	
		void Run();

	private:
		void UpdateEvents();
		void Update();
		void Render();
};

