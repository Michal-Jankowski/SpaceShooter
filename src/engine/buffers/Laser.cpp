#include "Laser.h"
#include <array>
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
// where:
// linePoints -> start & end coords
bool Laser::isColliding(std::array<glm::vec3, 2> linePoints, glm::vec3 sphereCoords, float radius)
{
	// solving quadratic equation of the form: au^2 + bu + c = 0
	glm::vec3 diffValues = glm::vec3(linePoints[1].x - linePoints[0].x, linePoints[1].y - linePoints[0].y, linePoints[1].z - linePoints[0].z);

	auto a = diffValues.x * diffValues.x + diffValues.y * diffValues.y + diffValues.z * diffValues.z;
	auto b = 2 * (diffValues.x * (linePoints[0].x - sphereCoords.x) + diffValues.y * (linePoints[0].y - sphereCoords.y) + diffValues.z * (linePoints[0].z - sphereCoords.z));
	auto c = sphereCoords.x * sphereCoords.x + sphereCoords.y * sphereCoords.y + sphereCoords.z * sphereCoords.z;
	c += linePoints[0].x * linePoints[0].x + linePoints[0].y * linePoints[0].y + linePoints[0].z * linePoints[0].z;
	c -= 2 * (sphereCoords.x * linePoints[0].x + sphereCoords.y * linePoints[0].y + sphereCoords.z * linePoints[0].z);
	c -= radius * radius;
	auto delta = b * b - 4 * a * c;

	if (abs(a) < std::numeric_limits<float>::epsilon() || delta < 0) {
		return false; // line does not intersect
	}
	return true; // line intersects or touches the sphere
}
