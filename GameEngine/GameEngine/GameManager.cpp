#include <map>
#include "GameState.h"
class GameManager {

	bool mouseClick = false;
	bool mouseHold = false;
	
	std::map<std::string, GameState>StateManager;

	void GameInit()
	{
	}

};