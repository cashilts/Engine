//Open GL libraries
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GL.h>

#include "Renderer.h"


#include <vector>


bool Renderer::drawGlScene()
{
	glClearColor(0.0, 0.0, 1.0, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

void Renderer::initGl()
{
	//Size the open gl viewport to be the same size as the window
	glViewport(0, 0, 640, 480);
	//Change projection matrix based on window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 100.0f);
	//Load the model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glShadeModel(GL_SMOOTH);
	//glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set The Blending Function For Translucency
	glClearDepth(1.0);		// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

bool Renderer::drawGameObject(GameObject* obj)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5);
	//TODO: REMOVE!! For testing only!
	glColor3f(1.0, 0.0, 0.0);
	if (!obj)
	{
		return false;
	}
	//TODO: Replace this function with Gl drawarrays version
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < obj->verticies.size(); i++)
	{
		glNormal3f(obj->normals[i].x, obj->normals[i].y, obj->normals[i].z);
		//glTexCoord2f(obj->uvs[i].x, obj->uvs[i].y);
		glVertex3f(obj->verticies[i].x, obj->verticies[i].y, obj->verticies[i].z);
	}
	glEnd();
	return true;
}
