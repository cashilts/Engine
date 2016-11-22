#pragma once
#include "GameState.h"
#include "Renderer.h"

#include <string>
#include <fstream>
//Menu state is a game state type that controls the menu screens the player interacts with
//These menus are modular and are created through text file templates



//Generic class for objects the menu creates
class MenuObject {
	friend class MenuState;
public:
	bool active;
	float xPos, yPos;
	Font* fontForMenu;
	virtual void updateObj(float mouseX, float mouseY, bool mouseClick) = 0;
	virtual void activateObj() { active = true; }
	~MenuObject() { delete fontForMenu; }
};

//Text objects created by the menu
class MenuText : public MenuObject {
	friend class MenuState;
public:
	std::string text;
	void updateObj(float mouseX, float mouseY, bool mouseClick) {
		Renderer::writeText(text.c_str(), fontForMenu, 1, 1, xPos, yPos);
	}
};

class MenuButton : public MenuObject {
public:
	std::string text;
	bool toggleButton = false;
	bool toggleState = false;
	float width, height;
	void updateObj(float mouseX, float mouseY, bool mouseClick) override;
	MenuObject* onClick;
	~MenuButton() { delete onClick; }
};

class MenuChange : public MenuObject {
public:
	std::string stateName;
	GameManager* callback;
	void updateObj(float mouseX, float mouseY, bool mouseClick);
	void activateObj() override;
	~MenuChange() { delete callback; }
};

//Menu state class, since all state calls are in the game manager it is the friend class of this state
class MenuState : public GameState {
	friend class GameManager;
public:;
	void Update(float mouseX, float mouseY, bool mouseClick) override; //Called every frame, override for basic game class update
	void OnStateEnter() override; //Called when the state is entered by the game manager
	void OnStateExit() override; //Called when the state is left by the game manager
	MenuState(char* MenuFile, GameManager* callbackClass); //Game states are created with a URL to the source
	MenuObject* loadMenuObject(std::ifstream& menu);
	void AddMenuObject(MenuObject* menuObj);
	~MenuState();
private:
	std::string fontName; //Stores the path of the font
	float menuWidth, menuHeight; //Stores the dimensions of the window to scale objects to the screen
	Font font; //Font used for the menu
	std::vector<MenuObject*> menuObjects; //Vector of all objects in the menu
};