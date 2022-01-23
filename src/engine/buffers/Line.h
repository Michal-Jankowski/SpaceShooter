#pragma once
#include "../shaders/ShaderProgram.h"
#include <glm/glm.hpp>
class Line
{
public:
	Line();
	Line(glm::vec3 start, glm::vec3 end);
	~Line();
	void draw();
	void setColor(const glm::vec4& color);
    void setColor(const glm::vec3 &color);
	void setPosition(const glm::vec3& start, const glm::vec3& end);
    glm::vec3 getStartPosition() const;
    glm::vec3 getEndPosition() const;
    glm::vec3 getNormalisedDir() const;
private:
	void setupBuffers();
	unsigned int m_VBO{ 0 }, m_VAO{ 0 }, m_IBO{ 0 };
	std::vector<float> m_vertices;
	std::vector<GLushort> m_verticesIndicies{ 0, 1 };
    glm::vec3 m_startPoint;
    glm::vec3 m_endPoint;
	glm::vec4 m_lineColor;
	bool needInitialising = false;


};

