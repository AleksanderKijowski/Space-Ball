#pragma once
#include "GameContextShared.hpp"
#include "KeybindsBuilder.hpp"
#include "Counter.hpp"
#include "ScaleProvide.hpp"
#include "LevelBuilder.hpp"

class LevelSelectionContext
{
private:

protected:
	GameContextShared* _context;
	std::shared_ptr<sf::RenderWindow> _window;
	std::shared_ptr<Map<string, int>> _keyBinds;
	std::shared_ptr<CounterPort> _port;
	std::shared_ptr<Counter> _counter;

public:
	LevelSelectionContext(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
	{
		// ToDo: Change keybinds path
		_context = context;
		_window = window;
		_keyBinds.reset(KeyBindsBuilder().Build(supportedKeys, MainMenuKeyBindsPath));
		_port.reset(new CounterPort());
		InitializeCounter();
	}

	virtual ~LevelSelectionContext()
	{
	}

private:
	void InitializeCounter()
	{
		var scale = ScaleProvider::Get(sf::Vector2f(_window->getSize()));
		var params = CounterParams();
		params.Size = sf::Vector2f(1920 * 4 / 6 * scale.x, 1080 * 4 / 6 * scale.y);
		params.Position = sf::Vector2f(1920 / 6 * scale.x, 1080 / 6 * scale.y);
		params.Title = "Select level:";
		params.StringList = LevelBuilder().GetLevelNames();
		params.Port = _port;
		_counter.reset(new Counter(params));
	}
};