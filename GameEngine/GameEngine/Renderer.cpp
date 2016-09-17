#include "Renderer.h"


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

float screenWidth;
float screenHeight;


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

	screenWidth = width;
	screenHeight = height;

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
	for ( uint16_t i = 0; i < obj->verticies.size(); i++)
	{
		glNormal3f(obj->normals[i].x, obj->normals[i].y, obj->normals[i].z);
		glTexCoord2f(obj->uvs[i].x, obj->uvs[i].y);
		glVertex3f(obj->verticies[i].x, obj->verticies[i].y, obj->verticies[i].z);
	}
	glEnd();
	xRot += 0.1;
	//yRot += 0.2;
	//zRot += 0.3;
	return true;
}

void Renderer::setPlayerRotation(float deltaAngle, float deltaAngleY)
{
	angle = 3.14159 + deltaAngle;
	angleY = deltaAngleY;
}


bool Renderer::loadTexture(const char* path, int* textureId)
{
	*textureId = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (*textureId == 0)
		return false;

	glBindTexture(GL_TEXTURE_2D, *textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return true;
}

bool Renderer::LoadFont(const char* filename, Font* font)
{
	rapidxml::file<> xml(filename);
	rapidxml::xml_document<> doc;

	doc.parse<0>(xml.data());
	Font newFont;
	rapidxml::xml_node<> *curNode = doc.first_node();
	curNode = curNode->first_node("pages");
	std::string path("Fonts/" + (std::string)curNode->first_node()->first_attribute("file")->value());
	if (!Renderer::loadTexture(path.c_str(), &newFont.textureId))
	{
		return false;
	}
	float width, height;
	glBindTexture(GL_TEXTURE_2D, newFont.textureId);
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	newFont.width = width;
	newFont.height = height;
	curNode = curNode->next_sibling("chars");
	int charAmount;
	sscanf_s(curNode->first_attribute()->value(), "%d",&charAmount);
	curNode = curNode->first_node();
	for (int i = 0; i < charAmount; i++)
	{
		Character newChar;
		int id; 
		sscanf_s(curNode->first_attribute("id")->value(), "%d",&id);
		sscanf_s(curNode->first_attribute("x")->value(), "%f", &newChar.x);
		//newChar.x /= width;
		sscanf_s(curNode->first_attribute("y")->value(), "%f", &newChar.y);
		//newChar.y /= height;
		sscanf_s(curNode->first_attribute("width")->value(), "%f", &newChar.width);
		//newChar.width /= width;
		sscanf_s(curNode->first_attribute("height")->value(), "%f", &newChar.height);
		//newChar.height /= height;
		sscanf_s(curNode->first_attribute("xoffset")->value(), "%f", &newChar.xOffset);
		//newChar.xOffset /= width;
		sscanf_s(curNode->first_attribute("yoffset")->value(), "%f", &newChar.yOffset);
		//newChar.yOffset /= height;
		sscanf_s(curNode->first_attribute("xadvance")->value(), "%f", &newChar.xAdvance);
		//newChar.xAdvance /= width;

		newFont.fontChars.insert(std::pair<int, Character>(id, newChar));
		curNode = curNode->next_sibling();
	}
	*font = newFont;
}

void Renderer::writeText(const char* text, Font* font,float letterWidth, float letterHeight,float x,float y)
{
	std::vector<glm::vec2> Verticies;
	std::vector<glm::vec2> UVs;
	int len = strlen(text);
	for (int i = 0; i < len; i++)
	{
		Character toDraw = font->fontChars.find(text[i])->second;
		x += toDraw.xOffset;
		//y -= toDraw.yOffset;

		glm::vec2 topLeftVert = glm::vec2(x, y + toDraw.height);
		glm::vec2 topRightVert = glm::vec2(x + toDraw.width, y + toDraw.height);
		glm::vec2 bottomRightVert = glm::vec2(x + toDraw.width, y);
		glm::vec2 bottomLeftVert = glm::vec2(x, y );

		x = x - toDraw.xOffset + toDraw.xAdvance;
		//y += toDraw.yOffset;

		Verticies.push_back(topLeftVert);
		Verticies.push_back(bottomLeftVert);
		Verticies.push_back(topRightVert);

		Verticies.push_back(bottomRightVert);
		Verticies.push_back(topRightVert);
		Verticies.push_back(bottomLeftVert);

		
		glm::vec2 bottomLeftUV = glm::vec2((toDraw.x/font->width), 1 - (toDraw.height/font->height + toDraw.y/font->height));
		glm::vec2 bottomRightUV = glm::vec2(toDraw.x / font->width + toDraw.width / font->width, 1 - (toDraw.height / font->height + toDraw.y / font->height));
		glm::vec2 topRightUV = glm::vec2(toDraw.x / font->width + toDraw.width / font->width, 1 - toDraw.y / font->height);
		glm::vec2 topLeftUV = glm::vec2(toDraw.x / font->width, 1 - toDraw.y / font->height);


		UVs.push_back(topLeftUV);
		UVs.push_back(bottomLeftUV);
		UVs.push_back(topRightUV);

		UVs.push_back(bottomRightUV);
		UVs.push_back(topRightUV);
		UVs.push_back(bottomLeftUV);
	}
	glBindTexture(GL_TEXTURE_2D, font->textureId);
	glBegin(GL_TRIANGLES);
	for (uint16_t i = 0; i < Verticies.size(); i++)
	{
		glNormal3f(0, 0, 1);
		glTexCoord2d(UVs[i].x, UVs[i].y);
		glVertex2f(Verticies[i].x, Verticies[i].y);
	}
	glEnd();
	
}

void Renderer::SetMenuPerspective()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
	glTranslatef(0, 0, -5);
}

void Renderer::MouseCoodinatesToScreen(float* mouseX, float* mouseY)
{

	GLdouble x, y, z,farX,farY,farZ;
	GLint viewport[4];
	GLdouble modelView[16];
	GLdouble Projection[16];
	GLfloat mouseZ;
	
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, Projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	

	*mouseY = (float)viewport[3] - *mouseY;
	glReadPixels(*mouseX,(int)mouseY, 1,1, GL_DEPTH_COMPONENT, GL_FLOAT, &mouseZ);
	gluUnProject(*mouseX, *mouseY,mouseZ, modelView, Projection, viewport, &x, &y, &z);

	*mouseX = (float)x;
	*mouseY = (float)y;
}


unsigned long getFileLength(std::ifstream& file)
{
	if (!file.good()) return 0;

	unsigned long pos = file.tellg();
	file.seekg(0, std::ios::end);
	unsigned long len = file.tellg();
	file.seekg(std::ios::beg);
	
	return len;
}


//Load shader takes a text file with open gl shader source code and loads it into memory.
int loadShader(char * filename, GLchar** ShaderSource, unsigned long* len)
{
	std::ifstream file;
	file.open(filename, std::ios::in); //Opens file as ASCII
	if (!file) return -1;

	*len = getFileLength(file);

	if (*len == 0) return -2; 

	*ShaderSource = new char[*len + 1];
	if (*ShaderSource == 0) return -3;

	*ShaderSource[*len] = 0;

	unsigned int i = 0;
	while (file.good())
	{
		*ShaderSource[i] = file.get();
		if (!file.eof()) i++;
	}

	*ShaderSource[i] = 0;
	file.close();
	return 0;
}

int unloadShader(GLchar** ShaderSource)
{
	if (*ShaderSource != 0)
	{
		delete[] *ShaderSource;
	}
	*ShaderSource = 0;
}


