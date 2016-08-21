#pragma once
#include "GameState.h"
class MenuState :GameState {
public:
	virtual void Update();
	virtual void OnStateEnter();
	virtual void OnStateExit();
private:
	MenuState(char* MenuFile);
};