
#include "GameObject.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <iostream>
#include <fstream>
bool createObjectFromNewFile(const char* filename, GameObject* obj)
{
	rapidxml::file<> xml(filename);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xml.data());
	rapidxml::xml_node<> *meshNode = doc.first_node();
	meshNode = meshNode->first_node("library_geometries", 0, true);
	meshNode = meshNode->first_node();
	meshNode = meshNode->first_node();

	return false;
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