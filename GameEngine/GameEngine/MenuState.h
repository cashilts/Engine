#pragma once
#include "GameState.h"
#include "Renderer.h"

#include <string>
//Menu state is a game state type that controls the menu screens the player interacts with
//These menus are modular and are created through text file templates



//Generic class for objects the menu creates
class MenuObject {
	friend class MenuState;
public:
	float xPos, yPos;
	Font* fontForMenu;
	virtual void updateObj(float mouseX, float mouseY, bool mouseClick) {}
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
	friend class MenuState;
public:
	std::string text;
	bool toggleButton = false;
	bool toggleState = false;
	float width, height;
	void updateObj(float mouseX, float mouseY, bool mouseClick) {
		glColor3f(1, 0,0);
		glTranslatef(0, 0, -1);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glVertex2f(xPos, yPos);
		glVertex2f(xPos + width, yPos);
		glVertex2f(xPos + width, yPos + height);
		glVertex2f(xPos, yPos + height);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0, 0, 1);
		glColor3f(1, 1, 1);
		Renderer::writeText(text.c_str(), fontForMenu, 1, 1, xPos, yPos);

		if (mouseClick && mouseX >= xPos && mouseX <= xPos + width && mouseY >= yPos && mouseY <= yPos + height)
		{
			onClick->fontForMenu = fontForMenu;
			toggleState = true;
		}

		if (toggleState)
		{
			onClick->updateObj(mouseX, mouseY, mouseClick);
		}
			
	}
	MenuObject* onClick;
};

class MenuChange : public MenuObject {
public:
	std::string stateName;
	GameManager* callback;
	void(GameManager::*fnPoint)(std::string);
	void updateObj(float mouseX, float mouseY, bool mouseClick) {
		(*callback.*fnPoint)(stateName);
	}
};

//Menu state class, since all state calls are in the game manager it is the friend class of this state
class MenuState : public GameState {
	friend class GameManager;
public:;
	void Update(float mouseX, float mouseY, bool mouseClick); //Called every frame, override for basic game class update
	void OnStateEnter(); //Called when the state is entered by the game manager
	void OnStateExit(); //Called when the state is left by the game manager
	MenuState(char* MenuFile, GameManager* callbackClass, void(GameManager::*function)(std::string)); //Game states are created with a URL to the source
	MenuObject* loadMenuObject(FILE* menu);
	~MenuState();
private:
	std::string fontName; //Stores the path of the font
	float menuWidth, menuHeight; //Stores the dimensions of the window to scale objects to the screen
	Font font; //Font used for the menu
	std::vector<MenuObject*> menuObjects; //Vector of all objects in the menu
};