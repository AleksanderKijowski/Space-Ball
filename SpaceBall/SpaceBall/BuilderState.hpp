#pragma once
#include "IState.hpp"
#include "BuilderContext.hpp"

class BuilderState : public IState, public BuilderContext
{
public:
	BuilderState(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
		: IState(), BuilderContext(context, window, supportedKeys)
	{
	}

	virtual void Update() override
	{
		UpdateKeys();

		var params = _context->GetBuilderUpdateParams();
		_tileSelection->Update(params.MouseCoordinates, params.MouseClicked);
		_buttonSelection->Update();
		_generateButton->Update(params.MouseCoordinates, params.MouseClicked);

		if (_port->Get() != notSelected)
		{
			if (_generatePort->Get() == activated)
			{
				var values = _buttonGrid->GetGridValues();
				var levelId = LevelBuilder().GenerateLevelToFileFromList(values);

				_context->PopState();

				ShowMessageBox(levelId);
			}
			else
			{
				_buttonGrid->Update(params.MouseCoordinates, params.MouseClicked);
			}
		}
	}

	virtual void Render() override
	{
		_tileSelection->Render(_window);
		_buttonSelection->Render(_window);

		if (_port->Get() != notSelected)
		{
			_buttonGrid->Render(_window);
			_generateButton->Render(_window);
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

	void ShowMessageBox(int generatedLevelId)
	{
		_context->PushNewState(std::shared_ptr<MessageBoxState>(new MessageBoxState(
			_context,
			_window,
			_context->GetSupportedKeys(),
			std::shared_ptr<MessageBoxOptions>(new MessageBoxOptions()),
			"Generated level: Level" + std::to_string(generatedLevelId),
			"OK",
			"")));
	}
};
