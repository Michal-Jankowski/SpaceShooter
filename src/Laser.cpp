#include "Laser.h"

Laser::Laser(glm::vec3 start, glm::vec3 end)
{
	startPoint = start;
	endPoint = end;
	lineColor = glm::vec3(1, 1, 1);
	vertices = {
			 start.x, start.y, start.z,
			 end.x, end.y, end.z,

	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &VBO);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Laser::~Laser()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &vao);
}

void Laser::draw()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 2);
}

bool Laser::isColliding(glm::vec3 pointPos, glm::vec4 sphereOrigin)
{
	auto xCoord = (pointPos.x - sphereOrigin.x) * (pointPos.x - sphereOrigin.x);
	auto yCoord = (pointPos.y - sphereOrigin.y) * (pointPos.y - sphereOrigin.y);
	auto zCoord = (pointPos.z - sphereOrigin.z) * (pointPos.z - sphereOrigin.z);

	auto sum = xCoord + yCoord + zCoord;
	auto doubleRadius = sphereOrigin.z * sphereOrigin.z; // z represents radius
	return sum < doubleRadius;
}
