#include "TestState.h"

int fontId;
GameObject* testObject;

void BasicTestingState::Update(float mouseX, float mouseY, bool mouseClick){
	glTranslatef(0, 0, -5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	Renderer::drawGameObject(testObject);
}

void BasicTestingState::OnStateEnter() {
	//Change projection matrix based on window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 100.0f);

	//Load the model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LIGHTING);
	Renderer::loadTexture("Textures/crate.bmp", &fontId);
	CreateObjectFromDAEFile("Models/Cube.dae",testObject);
	

}
void BasicTestingState::OnStateExit() {

}

BasicTestingState::BasicTestingState()
{
	testObject = new GameObject();
}