#pragma once

//Creates a static class (Utility class)
class Renderer
{
public:
	static bool drawGlScene();
	static bool loadObjFromFile(const char* filename, std::vector<glm::vec3> &verticies, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals);
private:
	Renderer() {}
};
