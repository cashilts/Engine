#pragma once
#include <glm.hpp>
#include <vector>
class GameObject {
public:
	//Model information
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	
};
bool createObjectFromFile(const char* filename, GameObject* obj);
