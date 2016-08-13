
#include "Main.h"

//Standard libraries 
#include "stdafx.h"
#include <stdio.h>
#include <string>

//For general multiplatform support
#include "SDL.h"

#include "Renderer.h"
#include "GameObject.h"




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

    //Create a platform independent open GL window
	mainWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	
	//If window could not be created end the program
	if (!mainWindow)
	{
		return 0;
	}
	
	//Get the rendering context
	mainContext = SDL_GL_CreateContext(mainWindow);

	SDL_GL_SetSwapInterval(1);
	


	//Begin main loop
	bool done = false;
	GameObject testObject;
	createObjectFromFile("Models/cube.obj", &testObject);
	Renderer::initGl();
	Renderer::drawGameObject(&testObject);
	SDL_GL_SwapWindow(mainWindow);
	while (!done)
	{
		
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				done = true;
			}
		}
		
	}
	return 0;

}