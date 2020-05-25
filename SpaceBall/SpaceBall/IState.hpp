#pragma once
#include "stdafx.h"

class IState
{
protected:
	IState() = default;
	
public:
	virtual ~IState() = default;

	virtual void Update() abstract;
	virtual void Render() abstract;
};