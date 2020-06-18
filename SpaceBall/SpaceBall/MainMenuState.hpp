#pragma once
#include "IState.hpp"
#include "MainMenuContext.hpp"
#include "Button.hpp"
#include "ArgumentOutOfRangeException.hpp"
#include "BuilderStateBuilder.hpp"
#include "LevelSelectionStateBuilder.hpp"

class MainMenuState : public IState, public MainMenuContext
{
public:
	MainMenuState(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
		: IState(), MainMenuContext(context, window, supportedKeys)
	{
	}

	virtual void Update() override
	{
		var params = _context->GetMainMenuUpdateParams();

		switch (_port->Get())
		{
			case unset:
				UpdateKeys();
				UpdateButtons(params);
				break;

			case newGame:
				SwitchToLevelSelectionView();
				_port->Reset();
				break;

			case build:
				_port->Reset();
				SwitchToBuilderView();
				break;

			case settings:
				_port->Reset();
				break;

			case exitState:
				ExitKeyPressed();
				break;

			default:
				_port->Reset();
				throw new ArgumentOutOfRangeException("MainMenuState update.");
		}
	}

	virtual void Render() override
	{
		_buttonList->Render(_window);
	}

private:
	void HandleToPort(Map<string, int>::iterator key)
	{
		if (key->first == "EXIT")
		{
			ExitKeyPressed();
		}
	}

	void ExitKeyPressed()
	{
		if (_exitPort->Get() == zero)
		{
			_context->PushNewState(std::shared_ptr<MessageBoxState>(new MessageBoxState(
				_context,
				_window,
				_context->GetSupportedKeys(),
				_exitPort,
				"Do you want to exit?",
				"Yes",
				"No")));
		}
		else if (_exitPort->Get() == first)
		{
			_window->close();
		}
		else if (_exitPort->Get() == second)
		{
			_port->Reset();
			_exitPort->Reset();
		}
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

	void UpdateButtons(MainMenuUpdateParams params)
	{
		_buttonList->Update(params.MouseCoordinates, params.MouseClicked);
	}

	void SwitchToBuilderView()
	{
		_context->PushNewState(BuilderStateBuilder().Build(_context, _window, _context->GetSupportedKeys()));
	}

	void SwitchToLevelSelectionView()
	{
		_context->PushNewState(LevelSelectionStateBuilder().Build(_context, _window, _context->GetSupportedKeys()));
	}
};