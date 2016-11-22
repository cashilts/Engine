#include "Engine.h"

Engine::Engine() {
	//References for the main window of the program and the rendering context
	SDL_GLContext mainContext;

	//Check if SDL Video game be initialized, if not end the program
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s("Could not init SDL");
		return;
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
	std::string windowName = "";
#ifdef _WIN32
	windowName = "Windows GL";
#else
	windowName = "Unix GL";
#endif

	SDL_DisplayMode curDisplayMode;
	SDL_GetDesktopDisplayMode(0, &curDisplayMode);


	//Create a platform independent open GL window
	mainWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	//If window could not be created end the program
	if (!mainWindow)
	{
		return;
	}

	//Get the rendering context
	mainContext = SDL_GL_CreateContext(mainWindow);

	SDL_GL_SetSwapInterval(1);

	Renderer::initGl(1024, 720);

	stateManager = new GameManager{};
	stateManager->GameInit();
}

bool Engine::Update() {
	inputManager.updateInputs();
	if (inputManager.getKeyState(keyName::exitKey)) return false;
	int mouseX, mouseY;
	bool click;
	click = inputManager.getMouseState(mouseX, mouseY);

	stateManager->GameLoop(mouseX, mouseY, click);

	SDL_GL_SwapWindow(mainWindow); //Refresh the window

	return true;
}


Engine::~Engine() {
	SDL_DestroyWindow(mainWindow);
	delete stateManager;
}