#include "GameManager.h"

MenuState testState("Menus/TestMenu.txt");


void GameManager::GameInit()
{
	testState.StateCallback = &GameManager::ChangeState;
	currentState = &testState;
	prevState = &testState;
}

void GameManager::GameLoop(float mouseX, float mouseY)
{
	if (stateChange)
	{
		prevState->OnStateExit();
		currentState->OnStateEnter();
		stateChange = false;
	}
	currentState->Update(mouseX, mouseY);
}

void GameManager::ChangeState(std::string stateName)
{

}