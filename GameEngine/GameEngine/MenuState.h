#pragma once
#include "GameState.h"
#include "Renderer.h"
#include <vector>

//Menu state is a game state type that controls the menu screens the player interacts with
//These menus are modular and are created through text file templates



//Generic class for objects the menu creates
class MenuObject {
public:
	float xPos, yPos;
};

//Text objects created by the menu
class MenuText : public MenuObject {
public:
	char* text;
};

//Menu state class, since all state calls are in the game manager it is the friend class of this state
class MenuState : public GameState {
	friend class GameManager;
public:
	void Update(); //Called every frame, override for basic game class update
	void OnStateEnter(); //Called when the state is entered by the game manager
	void OnStateExit(); //Called when the state is left by the game manager
	MenuState(char* MenuFile); //Game states are created with a URL to the source
private:
	char fontName[30]; //Stores the path of the font (REPLACE WITH STRING)
	float menuWidth, menuHeight; //Stores the dimensions of the window to scale objects to the screen
	Font font; //Font used for the menu
	std::vector<MenuObject> menuObjects; //Vector of all objects in the menu
};