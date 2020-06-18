#pragma once
#include "BuilderContext.hpp"
#include "GridButton.hpp"
#include "BuilderButtonGridOption.hpp"

class ButtonGrid
{
	sf::Vector2f _scale;

	std::shared_ptr<BuilderButtonSelectionOptions> _texturePort;
	std::shared_ptr<List<sf::Texture*>> _textures;
	
	sf::Color* _transparent;
	sf::Color* _white;
	sf::Color* _black;

	sf::Vector2f _gridButtonSize;
	sf::Vector2f _buttonSize;
	sf::Vector2f _intiialButtonGridOffset;

	std::shared_ptr<GridButton> _grid[GridSizeX][GridSizeY];

public:
	ButtonGrid(sf::Vector2f windowSize, std::shared_ptr<List<sf::Texture*>> textures, std::shared_ptr<BuilderButtonSelectionOptions> texturePort)
	{
		_scale = ScaleProvider::Get(windowSize);
		_texturePort = texturePort;
		_textures = textures;

		_transparent = new sf::Color(sf::Color::Transparent);
		_white = new sf::Color(255, 255, 255, 128);
		_black = new sf::Color(sf::Color::Black);

		Initialize();
	}

	virtual ~ButtonGrid()
	{
		delete _transparent;
		delete _white;
		// ToDo: Do destructor
		// ToDo: Check if contructors are virtual
	}

	void Update(sf::Vector2i mousePosition, bool isClicked)
	{
		for (var y = GridSizeY - 1; y >= 0; y--)
		{
			for (var x = GridSizeX - 1; x >= 0; x--)
			{
				var current = _grid[x][y];
				current->Update(mousePosition, isClicked);

				if (current->isDisabled && !current->HasTexture())
				{
					current->SetNewTexture(GetTextureForPort());
					current->SetValue(_texturePort->Get());
				}
			}
		}
	}

	void Render(std::shared_ptr<sf::RenderWindow> target)
	{

		for (var y = GridSizeY - 1; y >= 0; y--)
		{
			for (var x = GridSizeX - 1; x >= 0; x--)
			{
				_grid[x][y]->Render(target);
			}
		}
	}

	List<int> GetGridValues()
	{
		var result = List<int>();

		for (var y = 0; y < GridSizeY; y++)
		{
			for (var x = 0; x < GridSizeX; x++)
			{
				result.push_back(_grid[x][y]->GetValue());
			}
		}

		return result;
	}

private:
	void Initialize()
	{
		_gridButtonSize = sf::Vector2f(1920 * 4 / 6 / 15 * _scale.x, 1080 * 4 / 6 / 15 * _scale.y);
		_buttonSize = sf::Vector2f(1920 * 4 / 6 / 15 * _scale.x, 1080 * 4 / 6 / 15 * _scale.y);
		_intiialButtonGridOffset = sf::Vector2f(1920 * 3 / 12 * _scale.x, 1080 / 12 * _scale.y);

		var params = GridButtonParams();
		params.Size = _gridButtonSize;
		params.NormalColor = _transparent;
		params.HoverColor = _white;
		params.ClickedColor = _transparent;
		params.OutlineColor = _black;
		params.Scale = _scale;

		for (var y = 0; y < GridSizeY; y++)
		{
			params.Position = _intiialButtonGridOffset + sf::Vector2f(0, params.Size.y * y);

			for (var x = 0; x < GridSizeX; x++)
			{
				params.Position += sf::Vector2f(params.Size.x, 0);
				_grid[x][y].reset(new GridButton(params));
			}
		}
	}

	sf::Texture* GetTextureForPort()
	{
		var iterator = 0;
		for (var texture = _textures->begin(); texture != _textures->end(); texture++)
		{
			if (iterator == _texturePort->Get() - 1)
			{
				return *texture;
			}
			++iterator;
		}

		return nullptr;
	}
};