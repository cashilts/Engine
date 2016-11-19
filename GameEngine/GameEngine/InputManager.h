#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "SDL.h"

const int NUMKEYS = 6;
enum keyName {
	exitKey, enterKey, upKey, downKey, leftKey, rightKey
};

class InputManager {

	bool keyStates[NUMKEYS];
	SDL_Scancode keyCodes[NUMKEYS];
	int mouseX, mouseY;
	bool mouseClick;
	public: 
		bool exitState, enterState, upState, downState, leftState, rightState;
		InputManager();
		bool changeInputSource(std::string &filename);
		void updateInputs();
		bool getKeyState(keyName name);
		bool getMouseState(int &x, int &y);
		
};