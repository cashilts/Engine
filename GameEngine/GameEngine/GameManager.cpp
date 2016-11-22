#include "GameManager.h"


void GameManager::GameInit()
{
	
	StateManager["menuTest"] = new MenuState{ "Menus/TestMenu.txt",this};
	StateManager["TestingState"] = new BasicTestingState{};
	currentState = StateManager["menuTest"];
	prevState = currentState;
}

void GameManager::GameLoop(float mouseX, float mouseY,bool mouseClick)
{
	if (stateChange)
	{
		prevState->OnStateExit();
		currentState->OnStateEnter();
		stateChange = false;
	}
	currentState->Update(mouseX, mouseY,mouseClick);
}

void GameManager::addState(GameState* toAdd, std::string name) {
	StateManager[name] = toAdd;
}

void GameManager::ChangeState(std::string stateName)
{
	if (StateManager[stateName] != 0) {
		prevState = currentState;
		currentState = StateManager[stateName];
		stateChange = true;
	}
}

GameManager::GameManager()
{
}

GameManager::~GameManager() {
	for (std::map<std::string, GameState*>::iterator it = StateManager.begin(); it != StateManager.end(); it++) {
		delete it->second;
	}
}