#pragma once
#include"glm/glm.hpp"
#include <array>
class StaticMesh
{
public:
	std::array<glm::vec2, 4> getQuad();
	std::array<glm::vec3, 4> getPlainVertices();
	std::array<glm::vec2, 4> getPlainTexCoords();
	std::array<glm::vec3, 4> getPlainColors();
};

