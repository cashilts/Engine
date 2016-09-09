#pragma once

//Game state is a template class that is used to control different states of the overall game
//Game states create and destroy game objects and control how the game "flows" 
class GameState {
	friend class GameManger;
	public:
		virtual void Update(); //Update is where objects are updated with information based on the current frame and rendered
		virtual void OnStateEnter(); //Called when the state is entered in the game manager, used for loading and initialization
		virtual void OnStateExit(); //Called when the state is left and used for destruction
};