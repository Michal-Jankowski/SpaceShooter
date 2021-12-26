#pragma once
#include "../shaders/ShaderProgram.h"
#include "../../game/elements/Camera.h"
#include <glm/glm.hpp>
class Line
{
public:
	Line(glm::vec3 start, glm::vec3 end);
	~Line();
	void draw();
	bool isColliding(std::array<glm::vec3, 2> linePoints, glm::vec3 sphereCoords, float radius);
	void setColor(glm::vec4 color);
	void setMVP(glm::mat4 mvp);
private:
	void updateShader();
	unsigned int m_VBO{ 0 }, m_VAO{ 0 };
	std::vector<float> m_vertices;
    glm::vec3 m_startPoint;
    glm::vec3 m_endPoint;
	glm::vec4 m_lineColor;
	glm::mat4 m_MVPMatrix;

	bool needInitialising = false;
};

