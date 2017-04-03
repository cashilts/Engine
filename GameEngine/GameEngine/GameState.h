#pragma once
#include "Renderer.h"
#include <string>

//Game state is a template class that is used to control different states of the overall game
//Game states create and destroy game objects and control how the game "flows" 
class GameState {
	friend class GameManager;
	public:
		virtual void Update(float mouseX, float mouseY,bool mouseClick); //Update is where objects are updated with information based on the current frame and rendered
		virtual void OnStateEnter(); //Called when the state is entered in the game manager, used for loading and initialization
		virtual void OnStateExit(); //Called when the state is left and used for destruction
		GameManager* callback; //Used so the game state can callback to the state system
		void(GameManager::*fnPoint)(std::string);
	private:
		
};