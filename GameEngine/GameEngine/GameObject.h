#pragma once
#include <glm.hpp>
#include <vector>

//Game object contains classes and functions for managing and controlling 3d models

const int MAX_WEIGHTS = 2;

struct vertex {
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec2 uvs;
	glm::vec2 boneIndicies;
	glm::vec2 boneWeights;
};

class GameObject {
public:
	//Model information
	std::vector<vertex> verticies;
	std::vector<glm::mat4> bones;
	std::vector<glm::mat4> invTBone;
	std::vector<glm::mat4> bindMatrix; 
	glm::mat4 ibpInv;
	void RotateBone(float degrees, int index);
protected:
	float xPos;
	float yPos;
	float zPos;
};

bool CreateObjectFromDAEFile(const char* filename, GameObject* obj);
