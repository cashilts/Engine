
#include "Main.h"

//Standard libraries 
#include "stdafx.h"
#include <stdio.h>
#include <string>

//For general multiplatform support
#include "SDL.h"

#include "Renderer.h"
#include "GameObject.h"
#include "GameManager.h"

using namespace std;



//Entry point
int main(int argc, char* argv[])
{
	//References for the main window of the program and the rendering context
	SDL_Window *mainWindow;
	SDL_GLContext mainContext;

	//Check if SDL Video game be initialized, if not end the program
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s("Could not init SDL");
		return 0;
	}

	//Set Open GL pixel attributes and set buffers

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);


	//For testing. Change window name based on OS
	string windowName = "";
	#ifdef _WIN32
		windowName = "Windows GL";
	#else
		windowName = "Unix GL";
	#endif

	SDL_DisplayMode curDisplayMode;
	SDL_GetDesktopDisplayMode(0, &curDisplayMode);
	

    //Create a platform independent open GL window
	mainWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, curDisplayMode.w, curDisplayMode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	//If window could not be created end the program
	if (!mainWindow)
	{
		return 0;
	}
	
	//Get the rendering context
	mainContext = SDL_GL_CreateContext(mainWindow);

	SDL_GL_SetSwapInterval(1);
	
	Renderer::initGl(curDisplayMode.w, curDisplayMode.h);

	//Begin main loop

	GameManager game;
	game.GameInit();

	int mouseX = 0, mouseY = 0;

	Font font;
	bool done = false;
	bool mouseClick = false;
	int fontId;
	//Renderer::loadTexture("Textures/crate.bmp", &fontId);
	GameObject testObject;
	Renderer::xPos = 0;
	Renderer::yPos = 0;
	Renderer::zPos = 0;
	//CreateObjectFromDAEFile("Models/Cube.dae",&testObject);
	
	//Renderer::LoadFont("Fonts/BasicLatin.fnt", &font);
	SDL_GL_SwapWindow(mainWindow);
	while (!done)
	{
		//Renderer::drawGameObject(&testObject);
		//Renderer::writeText("Hi Alex! Love you!", &font,0.5f,0.5f,0,0);
		
		SDL_Event event;
		if (mouseClick)
		{
			mouseClick = false;
		}
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						done = true; break;
					case SDLK_UP:
						Renderer::zPos += 1;
						break;
					case SDLK_DOWN:
						Renderer::zPos -= 1;
						break;
				}

					
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				//Get mouse coords
				SDL_GetMouseState(&mouseX, &mouseY);
				/*
				//Use the halfwidth of the screen, dividing the screen into a negative side and a positive
				float halfWidth = curDisplayMode.w / 2;

				//Delta angle will be within -1 to 1 regardless of screen size
				float deltaAngle = (x - halfWidth)/halfWidth;

				//Change the angle so the entire screen spans pi (180 degrees) 
				deltaAngle *= -3.1419f;

				//Repeat for the Y, do not span pi entirely so the player cannot look straight up
				float halfHeight = curDisplayMode.h / 2;
				float deltaAngleH = (y - halfHeight) / halfHeight;
				deltaAngleH *= -3;

				//Send to the renderer
				Renderer::setPlayerRotation(deltaAngle, deltaAngleH);
				*/
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				mouseClick = true;
			}
		}
		game.GameLoop(mouseX, mouseY,mouseClick);
		SDL_GL_SwapWindow(mainWindow);
	}

	return 0;
}