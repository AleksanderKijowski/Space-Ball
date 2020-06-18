#pragma once
#include "BuilderContext.hpp"

class ButtonSelectionField
{
private:
	sf::Color* _transparentColor;
	sf::Color* _textColor;

	sf::Vector2f _scale;
	sf::Font* _font;
	const int _characterSize = 34;

	std::shared_ptr<List<sf::Texture*>> _textures;
	std::shared_ptr<BuilderButtonSelectionOptions> _port;

	sf::Vector2f _buttonSize;
	TextButton* _selectedText;
	TextureButton* _selectedButton;

	BuilderButtonSelectionOption _lastPortValue;
public:
	ButtonSelectionField(sf::Vector2f windowSize, std::shared_ptr<List<sf::Texture*>> textures, std::shared_ptr<BuilderButtonSelectionOptions> port)
	{
		_transparentColor = new sf::Color(sf::Color::Transparent);
		_textColor = new sf::Color(sf::Color::White);

		_scale = ScaleProvider::Get(windowSize);

		_textures = textures;
		_port = port;

		_font = new sf::Font();
		if (!_font->loadFromFile(DefaultFontPath))
		{
			throw new FileNotFoundException(DefaultFontPath);
		}

		_lastPortValue = notSelected;

		_buttonSize = sf::Vector2f(1920 / 12 * _scale.x, 1080 / 12 * _scale.y);
		Initialize();
	}

	~ButtonSelectionField()
	{
		delete _transparentColor;
		delete _textColor;
		delete _font;
		delete _selectedButton;
		delete _selectedText;
	}

	void Update()
	{
		var hasChanged = _lastPortValue != _port->Get();

		if (hasChanged && _lastPortValue == notSelected)
		{
			InitializeSelectedButton(_buttonSize);
		}
		else if (hasChanged)
		{
			_selectedButton->SetNewTexture(GetTextureForPort());
		}

		_lastPortValue = _port->Get();
	}

	void Render(std::shared_ptr<sf::RenderWindow> target)
	{
		_selectedText->Render(target);

		if (_lastPortValue != notSelected)
		{
			_selectedButton->Render(target);
		}
	}

private:
	void Initialize()
	{
		InitializeSelectedText(_buttonSize);
		InitializeSelectedButton(_buttonSize);
	}

	void InitializeSelectedText(sf::Vector2f buttonSize)
	{
		var params = TextButtonParams();
		params.Position = sf::Vector2f(0, 0);
		params.Size = buttonSize;
		params.NormalColor = _transparentColor;
		params.TextColor = _textColor;
		params.Font = _font;
		params.FontSize = _characterSize * _scale.y;
		params.Text = SelectedTxt;

		_selectedText = new TextButton(params);
	}

	void InitializeSelectedButton(sf::Vector2f buttonSize)
	{
		var params = TextureButtonParams();
		params.Size = buttonSize;
		params.Scale = _scale;
		params.Position = sf::Vector2f(1920 / 12 * _scale.x, 0);
		params.Texture = GetTextureForPort();

		params.Texture = *_textures->begin();

		_selectedButton = new TextureButton(params);
	}

	sf::Texture* GetTextureForPort()
	{
		var iterator = 0;
		for (var texture = _textures->begin(); texture != _textures->end(); texture++)
		{
			if (iterator == _port->Get() - 1)
			{
				return *texture;
				break;
			}
			++iterator;
		}

		return nullptr;
	}
};