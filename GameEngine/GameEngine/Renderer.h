#pragma once
#include "GameObject.h"
#include <map>
//Creates a static class (Utility class)

struct Character {
	float x;
	float y;
	float width;
	float height;
	float xAdvance;
	float xOffset;
	float yOffset;
};
struct Font {
	std::map<int, Character> fontChars;
	int textureId = 0;
	float width, height;
};

class Renderer
{
public:
	
	static bool drawGlScene();
	static bool drawGameObject(GameObject* obj);
	static void initGl(int width, int height);
	static void setPlayerRotation(float deltaAngle,float deltaAngleY);
	static void writeText(char* text, Font* font, float letterWidth, float letterHeight, float x, float y);
	static bool loadTexture(const char* path, int* textureId);
	static bool LoadFont(char* filename,Font* font);
	static void SetMenuPerspective(void);
private:
	static float LightAmbient[];
	static float LightDiffuse[];
	static float LightPosition[];
	Renderer() {}
};
