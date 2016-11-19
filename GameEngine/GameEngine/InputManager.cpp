#include "InputManager.h"

InputManager::InputManager() {
	changeInputSource(std::string{ "Config/controls.txt" });
}

bool InputManager::changeInputSource(std::string &fileName) {
	std::ifstream controlFile{ fileName };
	std::string func;
	while (controlFile >> func) {
		
		if (func == "exit") {
			std::string key;
			controlFile >> key;
			SDL_Scancode converted = SDL_GetScancodeFromName(key.c_str());
			keyCodes[exitKey] = converted;
		}
	}
	return true;
}

void InputManager::updateInputs() {
	SDL_Event eventCheck;
	while (SDL_PollEvent(&eventCheck)){
		if (eventCheck.type == SDL_KEYDOWN) {
			SDL_Scancode keyPressed = eventCheck.key.keysym.scancode;
			for (int i = 0; i < NUMKEYS; i++) {
				if (keyPressed == keyCodes[i]) {
					keyStates[i] = true;
					break;
				}
			}
		}
		else if (eventCheck.type == SDL_KEYUP) {
			SDL_Scancode keyPressed = eventCheck.key.keysym.scancode;
			for (int i = 0; i < NUMKEYS; i++) {
				if (keyPressed == keyCodes[i]) {
					keyStates[i] = false;
					break;
				}
			}
		}
		else if (eventCheck.type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&mouseX, &mouseY);
		}
		else if (eventCheck.type == SDL_MOUSEBUTTONDOWN) {
			mouseClick = true;
		}
		else if (eventCheck.type == SDL_MOUSEBUTTONUP) {
			mouseClick = false;
		}
	}
}


bool InputManager::getKeyState(keyName name) {
	return keyStates[name];
}

bool InputManager::getMouseState(int &x, int &y) {
	x = mouseX;
	y = mouseY;
	return mouseClick;
}