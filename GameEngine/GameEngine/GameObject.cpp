
#include "GameObject.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>



//determines how many characters in a string of numbers seperated by spaces to shift so the same number is not read again when the string is re-scanned
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

//Obj files do not allow skeleton data to be transfered, avoid this file type
bool createObjectFromOBJFile(const char* filename, GameObject* obj)
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
	//for (unsigned int i = 0; i < vertexIndices.size(); i++)
	//{
	//	unsigned int vertexIndex = vertexIndices[i];
	//	glm::vec3 vertex = temp_verticies[vertexIndex - 1];
	//	obj->verticies.push_back(vertex);
	//}
	//for (unsigned int i = 0; i < normalIndices.size(); i++)
	//{
	//	unsigned int normalIndex = normalIndices[i];
	//	glm::vec3 normal = temp_normals[normalIndex - 1];
	//	obj->normals.push_back(normal);
	//}
	//for (unsigned int i = 0; i < uvIndices.size(); i++)
	//{
	//	unsigned int uvIndex = uvIndices[i];
	//	glm::vec2 uv = temp_uvs[uvIndex - 1];
	//	obj->uvs.push_back(uv);
	//}
	//return true;
}

void recursivelyGet(rapidxml::xml_node<>* node, std::vector<glm::mat4>& bones, std::map<std::string, int>& nameIndex) {
	std::string id{ node->first_attribute("id")->value() };
	int index = nameIndex[id];
	node = node->first_node();
	std::istringstream matString{ std::string{ node->value() } };
	float x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3;
	matString >> x0;
	matString >> y0;
	matString >> z0;
	matString >> w0;
	matString >> x1;
	matString >> y1;
	matString >> z1;
	matString >> w1;
	matString >> x2;
	matString >> y2;
	matString >> z2;
	matString >> w2;
	matString >> x3;
	matString >> y3;
	matString >> z3;
	matString >> w3;
	glm::mat4 temp{ x0,y0,z0,w0,x1,y1,z1,w1,x2,y2,z2,w2,x3,y3,z3,w3 };
	bones[index] = temp;
	while (true) {
		node = node->next_sibling();
		if (node == 0) return;
		recursivelyGet(node, bones, nameIndex);
	}
	
}

bool CreateObjectFromDAEFile(const char* filename, GameObject* obj)
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

										  //Load the characters representing the verticies
	std::istringstream vertexChars{ sourceNode->first_node()->value() };

	//Temp vertex
	glm::vec3 vert;

	//Get string length 
	int num;
	while(vertexChars >> vert.x >> vert.y >> vert.z)
	{
		//Add the vertex into a temp list
		tempVerticies.push_back(vert);
	}

	//Move to the normals source
	sourceNode = sourceNode->next_sibling();

	//Load the characters representing the normals, then repeat loading process similar to vertex loading
	std::istringstream normalsChars{ sourceNode->first_node()->value() };
	glm::vec3 norm;


	while (normalsChars >> norm.x >> norm.y >> norm.z)
	{
		tempNormals.push_back(norm);
	}

	//Move to UV source, repeat the same process used to load normals and vertexs
	sourceNode = sourceNode->next_sibling();
	std::istringstream uvChars{ sourceNode->first_node()->value() };

	glm::vec2 uv;
	while (uvChars >> uv.x >> uv.y)
	{
		tempUvs.push_back(uv);
	}


	//Move to node containing face data, load indicies similar to how vertex data was loaded
	sourceNode = sourceNode->next_sibling("polylist");
	sscanf_s(sourceNode->first_attribute("count")->value(), "%d", &num);
	char* indicies = sourceNode->first_node("p")->value();
	unsigned int vertexIndex, normalIndex, uvIndex;
	num = strlen(indicies);
	for (int i = 0; i < num;)
	{
		sscanf_s(&indicies[i], "%d %d %d", &vertexIndex, &normalIndex, &uvIndex);
		vertexIndices.push_back(vertexIndex);
		normalIndices.push_back(normalIndex);
		uvIndices.push_back(uvIndex);

		i += getIndexLen(&indicies[i]) + 1;
		i += getIndexLen(&indicies[i]) + 1;
		i += getIndexLen(&indicies[i]) + 1;
	}

	//Order verticies, normals and UVs so that all coordinate with the same vertex based on their index
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		vertex tempVertex;
		unsigned int vertexIndex = vertexIndices[i];
		tempVertex.position = tempVerticies[vertexIndex];
		unsigned int normalIndex = normalIndices[i];
		tempVertex.normals = tempNormals[normalIndex];
		unsigned int uvIndex = uvIndices[i];
		tempVertex.uvs = tempUvs[uvIndex];
		obj->positions.push_back(tempVertex.position);
		obj->normals.push_back(tempVertex.normals);
		obj->uvs.push_back(tempVertex.uvs);
	}
	sourceNode = doc.first_node();
	sourceNode = sourceNode->first_node("library_controllers");
	sourceNode = sourceNode->first_node();
	sourceNode = sourceNode->first_node();
	sourceNode = sourceNode->first_node();
	sourceNode = sourceNode->next_sibling();

	std::map<std::string,int> boneNameIndexPair;
	std::string temp(sourceNode->first_node()->first_attribute("count")->value());
	std::istringstream ss(temp);

	int nameCount;
	ss >> nameCount;

	temp = std::string(sourceNode->first_node()->value());
	ss = std::istringstream(temp);
	for (int i = 0; i < nameCount; i++) {
		std::string name;
		ss >> name;
		boneNameIndexPair[name] = i;
	}

	sourceNode = sourceNode->next_sibling();
	sourceNode = sourceNode->next_sibling();

	temp = std::string(sourceNode->first_node()->first_attribute("count")->value());
	ss = std::istringstream(temp);
	int bonePosCount;
	ss >> bonePosCount;
	temp = std::string(sourceNode->first_node()->value());
	ss = std::istringstream(temp);
	std::vector<float> tempBoneWeights;

	for (int i = 0; i < bonePosCount; i++) {
		float tempWeight;
		ss >> tempWeight;
		tempBoneWeights.push_back(tempWeight);
	}
	sourceNode = sourceNode->next_sibling("vertex_weights");
	temp = std::string(sourceNode->first_attribute("count")->value());
	ss = std::istringstream(temp);
	int vertexCount;
	ss >> vertexCount;
	temp = std::string(sourceNode->first_node("vcount")->value());
	std::istringstream vCount(temp);
	temp = std::string(sourceNode->first_node("v")->value());
	std::istringstream values(temp);
	std::vector < std::pair<float*, int*>> tempBonePairs;
	std::vector<float>allweights;
	std::vector<int>allindicies;
	std::vector<int>counts;
	std::vector<int>startCount;
	int currentIndice = 0;
	for (int i = 0; i < vertexCount; i++) {
		startCount.push_back(currentIndice);
		int weightCount;
		vCount >> weightCount;
		counts.push_back(weightCount);
		for (int i = 0; i < weightCount; i++) {
			int indice;
			int weightIndex;
			values >> indice;
			values >> weightIndex;
			float weight = tempBoneWeights[weightIndex];
			allweights.push_back(weight);
			allindicies.push_back(indice);
		}
		currentIndice += weightCount;
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		
		vertex tempVertex;
		
		unsigned int vertexIndex = vertexIndices[i];
		tempVertex.position = tempVerticies[vertexIndex];
		if (counts[vertexIndex] < 2) {
			tempVertex.boneIndicies = glm::vec2{ allindicies[startCount[vertexIndex]],0 };
			tempVertex.boneWeights = glm::vec2{ allweights[startCount[vertexIndex]],0 };

		}
		else{
			tempVertex.boneIndicies = glm::vec2{ allindicies[startCount[vertexIndex]],allindicies[startCount[vertexIndex] + 1] };
			tempVertex.boneWeights = glm::vec2{ allindicies[startCount[vertexIndex]],allindicies[startCount[vertexIndex] + 1] };
		}
		unsigned int normalIndex = normalIndices[i];
		tempVertex.normals = tempNormals[normalIndex];
		unsigned int uvIndex = uvIndices[i];
		tempVertex.uvs = tempUvs[uvIndex];
		obj->indicies.push_back(tempVertex.boneIndicies);
		obj->weights.push_back(tempVertex.boneWeights);
	}

	sourceNode = doc.first_node();
	sourceNode = sourceNode->first_node("library_controllers");
	sourceNode = sourceNode->first_node();
	sourceNode = sourceNode->first_node();
	sourceNode = sourceNode->first_node("source");
	sourceNode = sourceNode->next_sibling();
	sourceNode = sourceNode->first_node();
	//std::vector<glm::mat4> boneCollection(30);
	std::istringstream matrixStream{ sourceNode->value() };
	glm::mat4 binv;
	for (int i = 0; i < nameCount; i++)
	{
		float x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3;
		matrixStream >> x0;
		matrixStream >> y0;
		matrixStream >> z0;
		matrixStream >> w0;
		matrixStream >> x1;
		matrixStream >> y1;
		matrixStream >> z1;
		matrixStream >> w1;
		matrixStream >> x2;
		matrixStream >> y2;
		matrixStream >> z2;
		matrixStream >> w2;
		matrixStream >> x3;
		matrixStream >> y3;
		matrixStream >> z3;
		matrixStream >> w3;
		glm::mat4 temp{ x0,y0,z0,w0,x1,y1,z1,w1,x2,y2,z2,w2,x3,y3,z3,w3 };
		binv *= temp;
	}
	obj->ibpInv =binv;
	sourceNode = doc.first_node();
	sourceNode = sourceNode->first_node("library_visual_scenes");
	sourceNode = sourceNode->first_node();
	sourceNode = sourceNode->first_node();
	sourceNode = sourceNode->first_node("node");
	std::vector<glm::mat4> boneCollection(30);
	//recursivelyGet(sourceNode,boneCollection,boneNameIndexPair);
	//while (true) {
	//	sourceNode = sourceNode->next_sibling();
	//	if (sourceNode == 0) break;
	//	recursivelyGet(sourceNode, boneCollection, boneNameIndexPair);
	//}
	obj->bones = boneCollection;
	doc.clear();
	return true;
	
}

void GameObject::RotateBone(float degrees, int index) {
}

