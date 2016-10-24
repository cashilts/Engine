#pragma once
#include <glm.hpp>
#include <vector>

struct vertex {
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec2 uvs;
	int* boneIndices;
	float* boneWeights;
	int boneCount;
};

class GameObject {
public:
	//Model information
	std::vector<vertex> verticies;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

protected:
	float xPos;
	float yPos;
	float zPos;
};

bool createObjectFromOBJFile(const char* filename, GameObject* obj);
bool CreateObjectFromDAEFile(const char* filename, GameObject* obj);
