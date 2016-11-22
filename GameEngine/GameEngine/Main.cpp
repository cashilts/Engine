
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
#include "Engine.h"
using namespace std;



//Entry point
int main(int argc, char* argv[])
{
	Engine *myEngine = new Engine{};
	//Begin main loop
	
	while (myEngine->Update()) {
	
	}
	delete myEngine;
	return 0;
}

//This was for looking around the screen, keep this for later
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