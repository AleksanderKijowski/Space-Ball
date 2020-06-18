#pragma once
#include "IState.hpp"
#include "MessageBoxContext.hpp"

class MessageBoxState : public IState, public MessageBoxContext
{
private:

public:
	MessageBoxState(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys,
		std::shared_ptr<MessageBoxOptions> port,
		string title,
		string first,
		string second)
		: IState(), MessageBoxContext(context, window, supportedKeys, port, title, first, second)
	{
	}
	virtual void Update()
	{
		UpdateKeys();
		var params = _context->GetBuilderUpdateParams();

		for (var button : _usedButtons)
		{
			button->Update(params.MouseCoordinates, params.MouseClicked);
		}

		if (_port->Get() != zero)
		{
			_context->PopState();
		}
	}

	virtual void Render()
	{
		_title->Render(_window);

		for (var button : _usedButtons)
		{
			button->Render(_window);
		}
	}

private:
	void HandleToPort(Map<string, int>::iterator key)
	{
		if (key->first == "BACK")
		{
			BackKeyPressed();
		}
	}

	void BackKeyPressed()
	{
		_context->PopState();
	}

	void UpdateKeys()
	{
		for (var key = _keyBinds->begin(); key != _keyBinds->end(); key++)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key->second)))
			{
				HandleToPort(key);
			}
		}
	}
};