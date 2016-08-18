#pragma once
#include "GameObject.h"
//Creates a static class (Utility class)
class Renderer
{
public:
	static bool drawGlScene();
	static bool drawGameObject(GameObject* obj);
	static void initGl(int width, int height);
	static void setPlayerRotation(float deltaAngle,float deltaAngleY);
private:
	static float LightAmbient[];
	static float LightDiffuse[];
	static float LightPosition[];
	Renderer() {}
};
