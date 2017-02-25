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

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec2> indicies;
	std::vector<glm::vec2> weights;
	std::vector<glm::mat4> bones;
	glm::mat4 ibpInv;
	void RotateBone(float degrees, int index);
protected:
	float xPos;
	float yPos;
	float zPos;
};

bool CreateObjectFromDAEFile(const char* filename, GameObject* obj);
