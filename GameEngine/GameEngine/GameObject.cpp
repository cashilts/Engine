
#include "GameObject.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <iostream>
#include <fstream>

int getIndexLen(const char* numStart)
{
	int i = 1;
	while (true)
	{
		if (numStart[i] == ' ')
		{
			return i;
		}
		i++;
	}
}

bool createObjectFromNewFile(const char* filename, GameObject* obj)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVerticies;
	std::vector<glm::vec3> tempNormals;
	std::vector<glm::vec2> tempUvs;

	//Load from filename
	rapidxml::file<> xml(filename);
	rapidxml::xml_document<> doc;

	//Parse the XML file into a tree
	doc.parse<0>(xml.data());

	//Navigate so that sourceNode points at the mesh data
	rapidxml::xml_node<> *sourceNode = doc.first_node();
	sourceNode = sourceNode->first_node("library_geometries", 0, true);
	sourceNode = sourceNode->first_node();//<geometry>
	sourceNode = sourceNode->first_node();//<mesh>
	sourceNode = sourceNode->first_node();//first <source> tag


	char* vertexChars = sourceNode->first_node()->value();

	glm::vec3 vert;
	int num;
	num = strlen(vertexChars);
	for (int i = 0; i < num;)
	{
		sscanf_s(&vertexChars[i], "%f %f %f", &vert.x, &vert.y, &vert.z);
		tempVerticies.push_back(vert);
		i += getIndexLen(&vertexChars[i]) + 1;
		i += getIndexLen(&vertexChars[i]) + 1;
		i += getIndexLen(&vertexChars[i]) + 1;
	}

	sourceNode = sourceNode->next_sibling();

	char* normalsChars = sourceNode->first_node()->value();

	glm::vec3 norm;
	num = strlen(normalsChars);
	for (int i = 0; i < num;)
	{
		sscanf_s(&normalsChars[i], "%f %f %f", &norm.x, &norm.y, &norm.z);
		tempNormals.push_back(norm);
		i += getIndexLen(&normalsChars[i]) + 1;
		i += getIndexLen(&normalsChars[i]) + 1;
		i += getIndexLen(&normalsChars[i]) + 1;
	}

	sourceNode = sourceNode->next_sibling("polylist");
	sscanf_s(sourceNode->first_attribute("count")->value(),"%d",&num);
	char* indicies = sourceNode->first_node("p")->value();
	unsigned int vertexIndex, normalIndex;
	num = strlen(indicies);
	for (int i = 0; i < num;)
	{
		sscanf_s(&indicies[i], "%d %d", &vertexIndex,&normalIndex);
		vertexIndices.push_back(vertexIndex);
		normalIndices.push_back(normalIndex);
		i += getIndexLen(&indicies[i]) + 1;
		i += getIndexLen(&indicies[i]) + 1;
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = tempVerticies[vertexIndex];
		obj->verticies.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = tempNormals[normalIndex];
		obj->normals.push_back(normal);
	}

	return true;
}



bool createObjectFromFile(const char* filename,GameObject* obj )
{
	//Create temporary vectors for the object data and indices
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_verticies;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_uvs;


	//Create the file referece 
	FILE *file;

	//Open the file
	errno_t e = fopen_s(&file, filename, "r");

	//If the file does not open return an error
	if (file == NULL)
	{
		return false;
	}
	
	//Continue until EOF
	while (1)
	{
		//Read the next string of characters
		char lineHeader[128];
		int res = fscanf_s(file, "%s", &lineHeader, sizeof(lineHeader));

		if (res == EOF)
		{
			break;
		}
		//.obj stores vertices with a prefix v
		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
			temp_verticies.push_back(vertex);
		}
		//.obj stores uv coorinates with a prefix vt
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf_s(file, "%f %f", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		//.obj stores normals with a prefix vn
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		//.obj stores faces with a prefix f
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], normalIndex[3], uvIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
		}
	}
	//Reindex verticies, normals and uvs to lines up so all line up correctly
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_verticies[vertexIndex - 1];
		obj->verticies.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		obj->normals.push_back(normal);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		obj->uvs.push_back(uv);
	}
	return true;
}