
#include "Main.h"

//Standard libraries 
#include "stdafx.h"
#include <stdio.h>
#include <string>

//For general multiplatform support
#include "SDL.h"


//Open GL libraries
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GL.h>



using namespace std;


bool drawGlScene()
{
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}


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

	//Set Open GL versions and initialize buffers
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//For testing. Change window name based on OS
	string windowName = "";
	#ifdef _WIN32
		windowName = "Windows GL";
	#else
		windowName = "Unix GL";
	#endif

    //Create a platform independent open GL window
	mainWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

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
	while (!done)
	{
		drawGlScene();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				done = true;
			}
		}
		SDL_GL_SwapWindow(mainWindow);
	}
	return 0;

}