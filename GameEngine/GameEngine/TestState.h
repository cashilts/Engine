#pragma once
#include "GameState.h"
class BasicTestingState : public GameState {
public:
	void Update(float mouseX, float mouseY, bool mouseClick);
	void OnStateEnter();
	void OnStateExit();
	BasicTestingState();
	~BasicTestingState();
};