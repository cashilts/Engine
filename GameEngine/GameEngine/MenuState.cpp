#include "MenuState.h"
#include "GameManager.h"

void MenuState::Update(float mouseX, float mouseY,bool mouseClick)
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
		if(menuObjects[i]->active)
		menuObjects[i]->updateObj(mouseX, mouseY, mouseClick);
	}
}

void MenuState::OnStateEnter()
{
	//Font should be loaded after state is entering, not when program is started, since texture loading cannot begin until opengl is initialized
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Renderer::LoadFont(fontName.c_str(), &font);
	glOrtho(0, menuWidth, 0, menuHeight, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -1);
}

void MenuState::OnStateExit()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

MenuObject* MenuState::loadMenuObject(std::ifstream& menu)
{
	std::string loadedObject;
	menu >> loadedObject;
	if (loadedObject == "t"){
		MenuText* textPoint = new MenuText;
		menu >> textPoint->text;
		menu >> textPoint->xPos;
		menu >> textPoint->yPos;
		//Add each menu object into the vector 
		textPoint->activateObj();
		return textPoint;
	}
	else if (loadedObject == "b"){
		MenuButton* buttonPoint = new MenuButton;
		menu >> buttonPoint->text;
		menu >> buttonPoint->xPos;
		menu >> buttonPoint->yPos;
		menu >> buttonPoint->width;
		menu >> buttonPoint->height;
		buttonPoint->onClick = loadMenuObject(menu);
		buttonPoint->activateObj();
		return buttonPoint;
	}
	else if (loadedObject == "c"){
		MenuChange* changePoint = new MenuChange;
		menu >> changePoint->stateName;
		changePoint->callback = callback;
		changePoint->activateObj();
		return changePoint;
	}
}

MenuState::MenuState(char* MenuFile, GameManager* callbackClass)
{
	callback = callbackClass;

	std::ifstream menu{ MenuFile };

	
	//All font files begin with font path followed by menu dimensions then by however menu objects are in the file
	menu >> fontName;

	menu >> menuWidth;
	menu >> menuHeight;

	int objectsInMenu;
	menu >> objectsInMenu;

	for (int i = 0; i < objectsInMenu; i++)
	{
		//For each object in menu, check the object type prefix
		menuObjects.push_back(loadMenuObject(menu));
	}

}



MenuState::~MenuState() {
	for each (MenuObject* obj in menuObjects)
	{
		delete obj;
	}
}

void MenuState::AddMenuObject(MenuObject* obj) {
	menuObjects.emplace_back(obj);
}

void MenuButton::updateObj(float mouseX, float mouseY, bool mouseClick) {
	glColor3f(1, 0, 0);
	glTranslatef(0, 0, -1);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glVertex2f(xPos, yPos);
	glVertex2f(xPos + width, yPos);
	glVertex2f(xPos + width, yPos + height);
	glVertex2f(xPos, yPos + height);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0, 0, 1);
	glColor3f(1, 1, 1);
	Renderer::writeText(text.c_str(), fontForMenu, 1, 1, xPos, yPos);

	if (mouseClick && mouseX >= xPos && mouseX <= xPos + width && mouseY >= yPos && mouseY <= yPos + height)
	{
		onClick->fontForMenu = fontForMenu;
		onClick->activateObj();
	}
	if (onClick->active)
	{
		onClick->updateObj(mouseX, mouseY, mouseClick);
	}

}

void MenuChange::activateObj() {
	callback->ChangeState(stateName);
}

void MenuChange::updateObj(float mouseX, float mouseY, bool mouseClick) {
}