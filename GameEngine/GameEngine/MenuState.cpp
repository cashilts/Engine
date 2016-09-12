#include "MenuState.h"

void MenuState::Update(float mouseX, float mouseY)
{
	Renderer::MouseCoodinatesToScreen(&mouseX, &mouseY);
	std::string coords = "Coords: " + std::to_string(mouseX) + " " + std::to_string(mouseY);
	
	//Renderer::SetMenuPerspective();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Renderer::writeText(coords.c_str(), &font, 1, 1, mouseX, mouseY);
	int length = menuObjects.size();
	for (int i =0; i<length; i++)
	{
		menuObjects[i]->fontForMenu = &font;
		menuObjects[i]->updateObj();
	}
}

void MenuState::OnStateEnter()
{
	//Font should be loaded after state is entering, not when program is started, since texture loading cannot begin until opengl is initialized
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Renderer::LoadFont(fontName.c_str(), &font);
	glOrtho(0, menuWidth, 0, menuHeight, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -1);
}

void MenuState::OnStateExit()
{
}

MenuState::MenuState(char* MenuFile)
{
	FILE* menu;
	
	errno_t e = fopen_s(&menu, MenuFile, "r");

	if (menu == NULL)
		return;

	std::string buffer;
	//All font files begin with font path followed by menu dimensions then by however menu objects are in the file
	fscanf_s(menu, "%s", &fontName);

	fscanf_s(menu, "%f", &menuWidth);
	fscanf_s(menu, "%f", &menuHeight);

	int objectsInMenu;
	fscanf_s(menu, "%d", &objectsInMenu);

	for (int i = 0; i < objectsInMenu; i++)
	{
		//For each object in menu, check the object type prefix
		fscanf_s(menu, "%s", &buffer);
		if (strcmp(buffer.c_str(), "t")==0)
		{
			MenuText newTextObj;
			
			fscanf_s(menu, "%s", &buffer);
			newTextObj.text = buffer.c_str();
			fscanf_s(menu, "%f", &newTextObj.xPos);
			fscanf_s(menu, "%f", &newTextObj.yPos);

			MenuText* textPoint = new MenuText;
			textPoint->text = newTextObj.text.c_str();
			textPoint->xPos = newTextObj.xPos;
			textPoint->yPos = newTextObj.yPos;
			//Add each menu object into the vector 
			
			menuObjects.push_back(textPoint);
		}

	}

}

MenuState::~MenuState() {
	for each (MenuObject* obj in menuObjects)
	{
		free(obj);
	}
}