#pragma once
#include <map>
#include "GameState.h"
#include "StateCollection.h"

class GameManager
{
	bool stateChange = true;
	std::map<std::string, GameState*>StateManager;
	GameState* currentState;
	GameState* prevState;
public:
	GameManager();
	void GameInit();
	void GameLoop(float mouseX, float mouseY, bool mouseClick);
	void ChangeState(std::string);
	void addState(GameState* toAdd, std::string name);
	~GameManager();
};