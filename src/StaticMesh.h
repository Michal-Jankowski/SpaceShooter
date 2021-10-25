#pragma once
#include"glm/glm.hpp"
#include <vector>
class StaticMesh
{
public:
	std::vector<glm::vec2> getQuad();
	std::vector<glm::vec3> getPlainVertices();
	std::vector<glm::vec2> getPlainTexCoords();
	std::vector<glm::vec3> getPlainColors();
};

