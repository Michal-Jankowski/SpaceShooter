#pragma once
#include "ShaderProgram.h"
#include <glm/glm.hpp>
class Laser
{
public:
	Laser(glm::vec3 start, glm::vec3 end);
	~Laser();
	void draw();
	bool isColliding(std::array<glm::vec3, 2> linePoints, glm::vec3 sphereCoords, float radius);
    glm::vec3 startPoint;
    glm::vec3 endPoint;
private:
	unsigned int VBO{ 0 }, vao{ 0 };
	std::vector<float> vertices;
	glm::vec3 lineColor;

	bool needInitialising = false;
};

