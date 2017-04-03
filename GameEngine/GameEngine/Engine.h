#pragma once
//For general multiplatform support
#include "SDL.h"

#include "Renderer.h"
#include "GameObject.h"
#include "GameManager.h"
#include "InputManager.h"

#include <stdio.h>
#include <string>

//Engine is the direct interface to allow clients to control the game

class Engine {
	SDL_Window *mainWindow; //SDL window state
	GameManager *stateManager; //Manager to handle the game state
	InputManager inputManager;


	public:
		Engine(); //Window is created when engine is initialized
		bool Update(); //This function must be called to have the game update, returns false when the game ends
		~Engine();
};