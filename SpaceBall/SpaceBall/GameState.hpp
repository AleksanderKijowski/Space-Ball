#pragma once
#include "IState.hpp"
#include "GameStateContext.hpp"
#include "Collider.hpp"

class GameState : public IState, public GameStateContext
{
private:
	float _elapsedTime;
	int lives = 3;

public:
	GameState(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys,
		std::shared_ptr<Level> level)
		: GameStateContext(context, window, supportedKeys, level)
	{
		_state = start;
	}

	virtual void Update()
	{
		var params = _context->GetGameStateUpdateParams();
		_elapsedTime = params.ElapsedTime;
		UpdateState();

		if (_state == game)
		{
			UpdateBall();
			CheckCollisions();
		}
		else if (_state == pause)
		{
			if (_exitPort->Get() == first)
			{
				_context->PopState();
			}
			else if (_exitPort->Get() == second)
			{
				_state = game;
				_exitPort->Reset();
			}
		}

		UpdateKeys();

		if (_state == end)
		{
			if (_exitPort->Get() == zero)
			{
				_context->PushNewState(std::shared_ptr<MessageBoxState>(new MessageBoxState(
					_context,
					_window,
					_context->GetSupportedKeys(),
					_exitPort,
					"Coingratulations!",
					"OK",
					"")));
			}
			else
			{
				_context->PopState();
			}

		}
		else if (_state == end)
		{
			if (_exitPort->Get() == zero)
			{
				_context->PushNewState(std::shared_ptr<MessageBoxState>(new MessageBoxState(
					_context,
					_window,
					_context->GetSupportedKeys(),
					_exitPort,
					"You lost!",
					"OK",
					"")));
			}
			else
			{
				_context->PopState();
			}

		}

		return;
	}

	virtual void Render()
	{
		if (_state != end)
		{
			for (var tile : _tiles)
			{
				tile->Render(_window);
			}

			_player->Render(_window);
			_ball->Render(_window);
		}

	}

private:
	void UpdateState()
	{
		if (_tiles.empty())
		{
			_state = end;
		}
		else if (false)
		{
			// ToDo: Add port checking for pause
		}
	}

	void HandleToPort(Map<string, int>::iterator key)
	{
		if (key->first == "EXIT")
		{
			ExitKeyPressed();
		}
		else if (_state == game && key->first == "MOVE_LEFT")
		{
			MoveLeftRequested();
		}
		else if (_state == game && key->first == "MOVE_RIGHT")
		{
			MoveRightRequested();
		}
		else if (_state == start && key->first == "SHOT")
		{
			_state = game;
		}
	}

	void ExitKeyPressed()
	{
		if (_state == start)
		{
			_context->PopState();
		}
		else if (_state == pause)
		{
			_state = game;
		}
		else if (_state == game)
		{
			if (_exitPort->Get() == zero)
			{
				_state = pause;

				_context->PushNewState(std::shared_ptr<MessageBoxState>(new MessageBoxState(
					_context,
					_window,
					_context->GetSupportedKeys(),
					_exitPort,
					"Do you want to exit?",
					"Yes",
					"No")));
			}
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

	void MoveLeftRequested()
	{
		_player->Update(_elapsedTime, MovementRequest::left);
	}

	void MoveRightRequested()
	{
		_player->Update(_elapsedTime, MovementRequest::right);
	}

	void UpdateBall()
	{
		_ball->Update(_elapsedTime);

		if (_ball->DidCollideWithFloor())
		{
			_state = start;
			lives--;
			if (lives > 0)
			{
				Reinitialize();
			}
			else
			{
				_state = end;
			}
		}
	}

	void CheckCollisions()
	{
		if (Collider().DoCollide(_player, _ball))
		{
			var offset = Collider().CalculateOffset(_player, _ball);
			_ball->OnCollision(player, offset);
		}

		var tile = _tiles.begin();
		while (tile != _tiles.end())
		{
			if (Collider().DoCollide(*tile, _ball))
			{
				_ball->OnCollision(Collider().DetermineCollisionType(*tile, _ball));
				_tiles.erase(tile);
				break;
			}
			else
			{
				tile++;
			}
		}
	}
};