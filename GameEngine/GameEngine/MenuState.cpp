#include "MenuState.h"

void MenuState::Update()
{
	Renderer::SetMenuPerspective();
	Renderer::writeText("Testing Menu State",&font,0.5f,0.5f,0,0);
}

void MenuState::OnStateEnter()
{
	//Font should be loaded after state is entering, not when program is started, since texture loading cannot begin until opengl is initialized
	Renderer::LoadFont(fontName, &font);
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

	char buffer[30];
	//All font files begin with font path followed by menu dimensions then by however menu objects are in the file
	fscanf_s(menu, "%s", &buffer);
	strcpy_s(fontName, buffer);

	fscanf_s(menu, "%f", &menuWidth);
	fscanf_s(menu, "%f", &menuHeight);

	int objectsInMenu;
	fscanf_s(menu, "%d", &objectsInMenu);

	for (int i = 0; i < objectsInMenu; i++)
	{
		//For each object in menu, check the object type prefix
		fscanf_s(menu, "%s", &buffer);
		if (strcmp(buffer, "t") == 0)
		{
			MenuText newTextObj;
			fscanf_s(menu, "%s", &buffer);
			newTextObj.text = buffer;
			fscanf_s(menu, "%f", &newTextObj.xPos);
			fscanf_s(menu, "%f", &newTextObj.yPos);

			//Add each menu object into the vector 
			menuObjects.push_back(newTextObj);
		}

	}

}