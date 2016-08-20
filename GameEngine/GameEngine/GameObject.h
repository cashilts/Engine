#pragma once
#include <glm.hpp>
#include <vector>
class GameObject {
public:
	//Model information
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
protected:
	float xPos;
	float yPos;
	float zPos;
};

bool createObjectFromFile(const char* filename, GameObject* obj);
bool createObjectFromNewFile(const char* filename, GameObject* obj);
