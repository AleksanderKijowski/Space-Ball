#pragma once
#include "ButtonList.hpp"
#include "BuilderButtonSelectionOptions.hpp"
#include "BuilderButtonTexts.h"

class BuilderButtonSelectionList : public ButtonList
{
private:
	sf::Color* _transparentColor;
	sf::Color* _textColor;

	sf::Font* _font;
	const int _characterSize = 48;

	TextButton* _selectedText;
public:
	BuilderButtonSelectionList(sf::Vector2f windowSize, std::shared_ptr<BuilderButtonSelectionOptions> port)
		: ButtonList(windowSize, port)
	{
		_transparentColor = new sf::Color(sf::Color::Transparent);
		_textColor = new sf::Color(sf::Color::White);

		_font = new sf::Font();

		if (!_font->loadFromFile(DefaultFontPath))
		{
			throw new FileNotFoundException(DefaultFontPath);
		}

		Initialize();
	}

	virtual ~BuilderButtonSelectionList()
	{
		delete _transparentColor;
		delete _textColor;
		delete _font;
		delete _selectedText;
	}
	
	virtual void Update(sf::Vector2i mousePosition, bool isClicked)
	{
		ButtonList::Update(mousePosition, isClicked);
	}

	virtual void Render(std::shared_ptr<sf::RenderWindow> target)
	{
		_selectedText->Render(target);

		ButtonList::Render(target);
	}

private:

	virtual void Initialize() override
	{
		var buttonSize = sf::Vector2f(1920 / 12 * 2 * _scale.x, 1080 / 12 * _scale.y);
		var buttonListPosition = sf::Vector2f(1920 / 12 * _scale.x, 1080 / 12 * 2 * _scale.y);

		InitializeSelectedField(buttonSize);

		// for (var i = 0; i < _quantity; i++)
		// {
		// 	params.Position = buttonListPosition + sf::Vector2f(0, (float)i * buttonSize.y);
		// 	params.Text = MainMenuTexts[i];
		// 
		// 	params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_port, i + 1));
		// 
		// 	var button = new TextButton(params);
		// 	_buttons.push_back(std::shared_ptr<Button>(button));
		// }
	}
	
	void InitializeSelectedField(sf::Vector2f buttonSize)
	{
		var params = TextButtonParams();
		params.Position = sf::Vector2f(1920 / 12 * _scale.x, 0);
		params.Size = buttonSize;
		params.NormalColor = _transparentColor;
		params.TextColor = _textColor;
		params.Font = _font;
		params.FontSize = _characterSize * _scale.y;
		params.Text = SelectedTxt;

		_selectedText = new TextButton(params);
	}
};