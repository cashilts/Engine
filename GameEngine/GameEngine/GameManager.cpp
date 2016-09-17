#include "GameManager.h"

MenuState* testState;
BasicTestingState* testingState;




void GameManager::GameInit()
{
	StateManager.insert(std::pair<std::string, GameState*>("menuTest", testState));
	StateManager.insert(std::pair<std::string, GameState*>("TestingState", testingState));
	currentState = testState;
	prevState = testState;
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



void GameManager::ChangeState(std::string stateName)
{
	prevState = currentState;
	currentState = StateManager.find(stateName)->second;
	stateChange = true;
}

GameManager::GameManager()
{
	testState = new MenuState("Menus/TestMenu.txt", this, &GameManager::ChangeState);
	testingState = new BasicTestingState();
}
