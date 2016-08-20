#pragma once
#include "GameState.h"
class MenuState :GameState {
	virtual void Update();
	virtual void OnStateEnter();
	virtual void OnStateExit();
};