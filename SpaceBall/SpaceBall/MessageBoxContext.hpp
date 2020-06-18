#pragma once
#include "GameContextShared.hpp"
#include "KeybindsBuilder.hpp"
#include "TextButton.hpp"
#include "ScaleProvide.hpp"
#include "MessageBoxOptions.hpp"

class MessageBoxContext
{
private:
	sf::Color* _transparentColor;
	sf::Color* _whiteColor;
	sf::Color* _greyColor;
	sf::Color* _blackColor;
	sf::Font* _font;

protected:
	GameContextShared* _context;
	std::shared_ptr<sf::RenderWindow> _window;
	std::shared_ptr<Map<string, int>> _keyBinds;
	std::shared_ptr<MessageBoxOptions> _port;

	std::shared_ptr<TextButton> _title;
	std::shared_ptr<TextButton> _first;
	std::shared_ptr<TextButton> _second;

	List<std::shared_ptr<TextButton>> _usedButtons;

public:
	MessageBoxContext(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys,
		std::shared_ptr<MessageBoxOptions> port,
		string title,
		string first,
		string second)
	{
		// ToDo: Change keybinds path.
		_context = context;
		_window = window;
		_keyBinds.reset(KeyBindsBuilder().Build(supportedKeys, BuilderKeyBindsPath));
		_port = port;

		InitializeColors();
		InitializeFont();
		Initialize(title, first, second);
	}

	virtual ~MessageBoxContext()
	{
		delete _transparentColor;
		delete _whiteColor;
		delete _greyColor;
		delete _blackColor;
		delete _font;
	}

private:
	void Initialize(string title, string first, string second)
	{
		var params = TextButtonParams();
		var screenSize = _window->getSize();
		var scale = ScaleProvider::Get(sf::Vector2f(screenSize));

		params.Size = sf::Vector2f(1920 * 2 / 6 * scale.x, 1080 * 1 / 6 * scale.y);
		params.NormalColor = _transparentColor;
		params.HoverColor = _whiteColor;
		params.ClickedColor = _greyColor;
		params.TextColor = _blackColor;
		params.Font = _font;
		params.FontSize = 44;

		params.Position = sf::Vector2f(1920 * 2 / 6 * scale.x, 1080 * 1 / 6 * scale.y);
		params.Text = title;
		params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_port, 0));
		_title.reset(new TextButton(params));

		params.Size = sf::Vector2f(1920 * 1 / 6 * scale.x, 1080 * 1 / 6 * scale.y);
		params.Position = sf::Vector2f(0, 1080 * 4 / 6 * scale.y);
		params.Text = first;
		params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_port, 1));
		_first.reset(new TextButton(params));
		_usedButtons.push_back(_first);

		if (!second.empty())
		{
			params.Position = sf::Vector2f(1920 * 5 / 6 * scale.x, 1080 * 4 / 6 * scale.y);
			params.Text = second;
			params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_port, 2));
			_second.reset(new TextButton(params));
			_usedButtons.push_back(_second);
		}
	}

	void InitializeColors()
	{
		_transparentColor = new sf::Color(sf::Color::Transparent);
		_whiteColor = new sf::Color(255, 255, 255, 128);
		_greyColor = new sf::Color(128, 128, 128, 128);
		_blackColor = new sf::Color(sf::Color::Black);
	}

	void InitializeFont()
	{
		_font = new sf::Font();

		if (!_font->loadFromFile(DefaultFontPath))
		{
			throw new FileNotFoundException(DefaultFontPath);
		}
	}
};