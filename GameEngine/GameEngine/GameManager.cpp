#include "GameManager.h"

MenuState testState("Menus/TestMenu.txt");

void GameManager::GameInit()
{

	currentState = &testState;
	prevState = &testState;
}

void GameManager::GameLoop()
{
	if (stateChange)
	{
		prevState->OnStateExit();
		currentState->OnStateEnter();
		stateChange = false;
	}
	currentState->Update();
}