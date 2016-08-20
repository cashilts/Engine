//Open GL libraries
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GL.h>

#include "Renderer.h"


#include <vector>

//Default lighting float arrays, these values are for testing only
//Amient and diffuse are RGBA values, position is XYZ and the way the light points
float Renderer::LightAmbient[] = { 0.5f,0.5f,0.5f,1 };
float Renderer::LightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
float Renderer::LightPosition[] = { 0,0,0,1.0f };
float xRot = 0;
float yRot = 0;
float zRot = 0;

//Player position and angle
float xPos = 0;
float yPos = 0;
float zPos = 2;

float angle = 3.14159;
float angleY = 0;
const int distance = 5;

bool Renderer::drawGlScene()
{
	glClearColor(0.0, 0.0, 1.0, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

void Renderer::initGl(int width, int height)
{
	//Size the open gl viewport to be the same size as the window
	glViewport(0, 0, width, height);
	//Change projection matrix based on window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 100.0f);
	//Load the model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Initiallize lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set The Blending Function For Translucency
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// This Will Clear The Background Color
	glClearDepth(1.0);		// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
														// Enables Smooth Color Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

}

bool Renderer::drawGameObject(GameObject* obj)
{
	float lookObjy = sin(angleY) * distance + yPos;
	float xzRate = abs(cos(angleY) * distance);
	float lookObjx = sin(angle) * xzRate + xPos;
	float lookObjz = cos(angle) * xzRate + zPos;

	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(xPos, yPos, zPos, lookObjx, lookObjy, lookObjz, 0, 1, 0);
	glTranslatef(0.0, 0.0, -5);
	glRotatef(xRot, 1.0, 0, 0);
	glRotatef(yRot, 0, 1.0, 0);
	glRotatef(zRot, 0, 0, 1);
	/*float modelMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelMatrix);
	float projectionMatrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);*/
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
	xRot += 0.1;
	yRot += 0.2;
	zRot += 0.3;
	return true;
}

void Renderer::setPlayerRotation(float deltaAngle, float deltaAngleY)
{
	angle = 3.14159 + deltaAngle;
	angleY = deltaAngleY;
}
