#pragma once
#include "stdafx.h"

class GameContext;

class IState
{
private:
	GameContext* _context;
	
public:
	IState(GameContext* context)
	{
		_context = context;
	}
	
	virtual ~IState() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;
};