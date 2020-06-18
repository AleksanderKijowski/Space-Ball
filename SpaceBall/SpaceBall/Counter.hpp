#pragma once
#include "TextButton.hpp"
#include "FileNotFoundException.hpp"
#include "CounterPort.hpp"

struct CounterParams
{
	sf::Vector2f Size;
	sf::Vector2f Position;
	string Title;
	List<string> StringList;
	std::shared_ptr<CounterPort> Port;
};

class Counter
{
private:
	class InternalPort : public IOption
	{
	public:
		void SetValue(int value)
		{
			if (value == 0)
			{
				Value = 0;
			}
			else
			{
				Value = value > 0
					? ++Value
					: --Value;
			}
		}

		void Reset()
		{
			Value = 1;
		}

		int Get() const
		{
			return Value;
		}
	};

	sf::Vector2f _size;
	sf::Vector2f _position;
	string _titleText;
	List<string> _stringList;
	std::shared_ptr<CounterPort> _port;
	int _selectedItem;

	std::shared_ptr<InternalPort> _internalPort;

	std::shared_ptr<TextButton> _title;
	std::shared_ptr<TextButton> _textField;
	std::shared_ptr<TextButton> _decrement;
	std::shared_ptr<TextButton> _increment;
	std::shared_ptr<TextButton> _accept;

	sf::Color* _transparentColor;
	sf::Color* _blackColor;
	sf::Color* _whiteColor;
	sf::Color* _greyColor;
	sf::Font* _font;

	List<std::shared_ptr<TextButton>> _usedButtons;

public:
	Counter(CounterParams params)
	{
		_size = params.Size;
		_position = params.Position;
		_titleText = params.Title;
		_stringList = params.StringList;
		_port = params.Port;
		_selectedItem = 0;

		_internalPort.reset(new InternalPort());
		InitalizeFont();
		InitializeColors();

		if (!_stringList.empty())
		{
			_selectedItem = 1;
			_internalPort->Reset();
			Initialize();
		}
	}

	virtual ~Counter()
	{
		delete _transparentColor;
		delete _blackColor;
		delete _whiteColor;
		delete _greyColor;
		delete _font;
	}

	virtual void Update(sf::Vector2i mousePosition, bool isClicked)
	{
		var value = _internalPort->Get();
		var count = _stringList.size();

		if (value != 0)
		{
			_usedButtons.clear();

			if (value > 1)
			{
				_usedButtons.push_back(_decrement);
			}
			
			if (value < count)
			{
				_usedButtons.push_back(_increment);
			}

			for (var button : _usedButtons)
			{
				button->Update(mousePosition, isClicked);
			}

			if (_selectedItem != _internalPort->Get())
			{
				_selectedItem = _internalPort->Get();

				var iterator = 1;
				for (var i = _stringList.begin(); i != _stringList.end(); i++)
				{
					if (_selectedItem == iterator)
					{
						var params = TextButtonParams();
						params.NormalColor = _transparentColor;
						params.HoverColor = _greyColor;
						params.ClickedColor = _whiteColor;
						params.TextColor = _blackColor;
						params.Font = _font;
						params.FontSize = 44;
						params.Size = sf::Vector2f(_size.x * 3 / 5, _size.y / 5);
						params.Position = sf::Vector2f(_size.x / 5, _size.y * 2 / 5) + _position;
						params.Text = *i;
						params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_internalPort, 1));
						_textField.reset(new TextButton(params));
						_textField.reset(new TextButton(params));
						break;
					}

					++iterator;
				}
			}

			_accept->Update(mousePosition, isClicked);
		}
		else
		{
			_port->SetValue(_selectedItem - 1);
			_internalPort->Reset();
		}
	}

	virtual void Render(std::shared_ptr<sf::RenderWindow> target)
	{
		if (_internalPort->Get() == 0)
		{
			return;
		}

		_textField->Render(target);
		_accept->Render(target);
		_title->Render(target);

		for (var button : _usedButtons)
		{
			button->Render(target);
		}
	}

private:
	void InitializeColors()
	{
		_transparentColor = new sf::Color(sf::Color::Transparent);
		_whiteColor = new sf::Color(255, 255, 255, 128);
		_greyColor = new sf::Color(128, 128, 128, 128);
		_blackColor = new sf::Color(sf::Color::Black);
	}

	void Initialize()
	{
		var params = TextButtonParams();
		params.NormalColor = _transparentColor;
		params.HoverColor = _greyColor;
		params.ClickedColor = _whiteColor;
		params.TextColor = _blackColor;
		params.Font = _font;
		params.FontSize = 44;

		params.Size = sf::Vector2f(_size.x, _size.y / 5);
		params.Position = _position;
		params.Text = _titleText;
		params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_internalPort, 0));
		_title.reset(new TextButton(params));

		params.Size = sf::Vector2f(_size.x / 15, _size.y / 15);
		params.Position = sf::Vector2f(_size.x / 15, _size.y * 7 / 15) + _position;
		params.Text = "-";
		params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_internalPort, -1));
		_decrement.reset(new TextButton(params));

		params.Size = sf::Vector2f(_size.x / 15, _size.y / 15);
		params.Position = sf::Vector2f(_size.x * 13 / 15, _size.y * 7 / 15) + _position;
		params.Text = "+";
		params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_internalPort, 1));
		_increment.reset(new TextButton(params));

		params.Size = sf::Vector2f(_size.x * 3 / 5, _size.y / 5);
		params.Position = sf::Vector2f(_size.x / 5, _size.y * 2 / 5) + _position;
		params.Text = _stringList.front();
		params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_internalPort, 1));
		_textField.reset(new TextButton(params));

		params.Size = sf::Vector2f(_size.x / 5, _size.y / 5);
		params.Position = sf::Vector2f(0, _size.y * 4 / 5) + _position;
		params.Text = "OK";
		params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_internalPort, 0));
		_accept.reset(new TextButton(params));
	}

	void InitalizeFont()
	{
		_font = new sf::Font();

		if (!_font->loadFromFile(DefaultFontPath))
		{
			throw new FileNotFoundException(DefaultFontPath);
		}
	}
};