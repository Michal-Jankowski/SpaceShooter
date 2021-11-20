#pragma once
#include "ShaderProgram.h"
#include <glm/glm.hpp>
class Laser
{
public:
	Laser(glm::vec3 pos1, glm::vec3 vector);
	~Laser();
	void draw();
	bool isColliding(std::array<glm::vec3, 2> linePoints, glm::vec3 sphereCoords, float radius);
private:
	unsigned int VBO{ 0 }, vao{ 0 };
	std::vector<float> vertices;
	glm::vec3 startPoint;
	glm::vec3 endPoint;
	glm::vec3 lineColor;
	bool needInitialising = false;
};
