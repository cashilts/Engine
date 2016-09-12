#pragma once
#include <map>
#include "GameState.h"
#include "StateCollection.h"

class GameManager
{
public:
	void GameInit();
	void GameLoop(float mouseX, float mouseY);
	void ChangeState(std::string);
	GameState* currentState;
	GameState* prevState;
	
private:
	bool mouseClick = false;
	bool mouseHold = false;
	bool stateChange = true;
	std::map<std::string, GameState>StateManager;
	
	
};