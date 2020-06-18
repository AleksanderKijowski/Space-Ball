#pragma once
#include "stdafx.h"
#include "GameContextShared.hpp"
#include "Level.hpp"
#include "KeybindsBuilder.hpp"
#include "BuilderResources.h"
#include "ScaleProvide.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "CounterPort.hpp"
#include "MessageBoxOptions.hpp"

class GameStateContext
{
private:

protected:
	enum GameStateState
	{
		start,
		game,
		pause,
		end,
		lose,
	};

	GameStateState _state;
	GameContextShared* _context;
	std::shared_ptr<sf::RenderWindow> _window;
	std::shared_ptr<Map<string, int>> _keyBinds;
	std::shared_ptr<MessageBoxOptions> _exitPort;
	std::shared_ptr<MessageBoxOptions> _endPort;
	std::shared_ptr<Level> _level;

	std::shared_ptr<List<sf::Texture*>> _textures;
	sf::Texture* _playerTexture;
	List<std::shared_ptr<Tile>> _tiles;
	std::shared_ptr<Player> _player;
	std::shared_ptr<Ball> _ball;
	int playerLives = 3;

public:
	GameStateContext(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys,
		std::shared_ptr<Level> level)
	{
		// ToDo: Change keybinds path
		_context = context;
		_window = window;
		_keyBinds.reset(KeyBindsBuilder().Build(supportedKeys, GameStateKeybindsPath));
		_exitPort.reset(new MessageBoxOptions());
		_endPort.reset(new MessageBoxOptions());
		_level = level;
		InitializeTextures();
		InitializeTiles();
		InitializePlayer();
		InitializeBall();
	}

	virtual ~GameStateContext()
	{
	}
protected:
	void Reinitialize()
	{
		InitializePlayer();
		InitializeBall();
	}

private:
	void InitializeTextures()
	{
		_textures.reset(new List<sf::Texture*>());

		for (var path : BuilderPaths)
		{
			var texture = new sf::Texture();

			if (texture->loadFromFile(path))
			{
				_textures->push_back(texture);
			}
			else
			{
				throw new FileNotFoundException(path);
			}
		}

		_playerTexture = new sf::Texture();

		if (!_playerTexture->loadFromFile(PlayerTexturePath))
		{
			throw new FileNotFoundException(PlayerTexturePath);
		}
	}

	void InitializeTiles()
	{
		var sizeX = _level->GetSizeX();
		var sizeY = _level->GetSizeY();
		var values = _level->GetValues();
		var scale = ScaleProvider::Get(sf::Vector2f(_window->getSize()));
		var tileSize = sf::Vector2f(1920 * 4 / 5 / 15 * scale.x, 1080 * 4 / 5 / 15 * scale.y);
		var tilePosition = sf::Vector2f();
		var tileTexture = &sf::Texture();
		var isBreakable = true;
		var value = 0;

		for (var y = 0; y < sizeY; y++)
		{
			for (var x = 0; x < sizeX; x++)
			{
				value = values.front();
				values.pop_front();
				
				if (value != 0)
				{
					tilePosition = sf::Vector2f(tileSize.x * x, tileSize.y * y);
					tileTexture = GetTextureById(value - 1);
					isBreakable = value != 3;

					_tiles.push_back(std::shared_ptr<Tile>(new Tile(tileSize, tilePosition, tileTexture, isBreakable)));
				}
			}
		}
		
	}

	void InitializePlayer()
	{

		var windowSize = _window->getSize();
		var scale = ScaleProvider::Get(sf::Vector2f(windowSize));
		var position = sf::Vector2f(1920 * 2 / 5 * scale.x, windowSize.y - 50 * scale.y);
		var boundaries = sf::Vector2f(windowSize.x * 4 / 5, windowSize.y);
		var size = sf::Vector2f(1920 * 1 / 6 * scale.x, 50 * scale.y);

		_player.reset(new Player(size, position, boundaries, scale, _playerTexture));
	}

	void InitializeBall()
	{
		var windowSize = _window->getSize();
		var scale = ScaleProvider::Get(sf::Vector2f(windowSize));
		var position = sf::Vector2f(1920 * 2 / 5 * scale.x, windowSize.y - 100 * scale.y);
		var boundaries = sf::Vector2f(windowSize.x * 4 / 5, windowSize.y);

		_ball.reset(new Ball(position, boundaries, scale, 230));
	}

	sf::Texture* GetTextureById(int id)
	{
		var iterator = 0;
		for (var texture = _textures->begin(); texture != _textures->end(); texture++)
		{
			if (iterator == id)
			{
				return *texture;
				break;
			}
			++iterator;
		}

		return nullptr;
	}
};