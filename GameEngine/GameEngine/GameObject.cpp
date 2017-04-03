
#include "GameObject.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
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
	Assimp::Importer colladaImporter;
	const aiScene* scene = colladaImporter.ReadFile(filename, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	aiMesh *model2 = scene->mMeshes[0];
	std::vector<vertex> tempVerticies;
	for (int i = 0; i < model2->mNumVertices; i++) {
		vertex tempVertex;
		tempVertex.position = glm::vec3(model2->mVertices[i].x,model2->mVertices[i].y,model2->mVertices[i].z);
		tempVertex.normals =  glm::vec3(model2->mNormals[i].x,model2->mNormals[i].y,model2->mNormals[i].z);
		tempVerticies.emplace_back(tempVertex);
		//obj->uvs.emplace_back(glm::vec2(model2->mTextureCoords[i]->x,model2->mTextureCoords[i]->y));
	}
	for (int i = 0; i < model2->mNumBones; i++) {
		aiMatrix4x4 bone = model2->mBones[i]->mOffsetMatrix;
		obj->bindMatrix.emplace_back(glm::mat4x4(bone.a1, bone.b1, bone.c1, bone.d1, bone.a2, bone.b2, bone.c2, bone.d2, bone.a3, bone.b3, bone.c3, bone.d3, bone.a4, bone.b4, bone.c4, bone.d4));
		obj->invTBone.emplace_back(glm::inverse(obj->bindMatrix[i]));
		obj->bones.emplace_back(obj->bindMatrix[i] * obj->invTBone[i]);
		int numWeights = model2->mBones[i]->mNumWeights;
		for (int j = 0; j < numWeights; j++) {
			aiVertexWeight tempWeight = model2->mBones[i]->mWeights[j];
			if (tempVerticies[tempWeight.mVertexId].boneWeights.x != 0) {
				tempVerticies[tempWeight.mVertexId].boneWeights.y = 1 - tempVerticies[tempWeight.mVertexId].boneWeights.x;
				tempVerticies[tempWeight.mVertexId].boneIndicies.y = i;
			}
			else {
				tempVerticies[tempWeight.mVertexId].boneWeights.x = tempWeight.mWeight;
				tempVerticies[tempWeight.mWeight].boneIndicies.x = i;
			}
		}
	}

	int numFaces = model2->mNumFaces;

	for (int i = 0; i < numFaces; i++) {
		for (int j = 0; j < model2->mFaces[i].mNumIndices; j++) {
			vertex temp = (tempVerticies[model2->mFaces[i].mIndices[j]]);
			obj->verticies.emplace_back(temp);
		}
	}

	return true;
	
}

void GameObject::RotateBone(float degrees, int index) {
}

