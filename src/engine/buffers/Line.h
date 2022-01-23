#pragma once
#include "../shaders/ShaderProgram.h"
#include <glm/glm.hpp>
class Line
{
public:
	Line(const glm::vec3& start, const glm::vec3& end);
	Line(const std::vector<glm::vec3>& points);
	~Line();
	void draw();
	void clearBuffer();
	void setColor(const glm::vec4& color);
    void setColor(const glm::vec3& color);
	void setPosition(const std::vector<glm::vec3>& points);
	void setMultiplePositions(const std::vector<glm::vec3>& points);
    glm::vec3 getStartPosition() const;
    glm::vec3 getEndPosition() const;
    glm::vec3 getNormalisedDir() const;
private:
	void setupBuffers();
	GLuint m_VBO{ 0 }, m_VAO{ 0 }, m_IBO;
	signed long long  m_prev{ 0 };
	std::vector<glm::vec3> m_vertices;
	std::vector<GLushort> m_verticesIndicies;
    glm::vec3 m_startPoint;
    glm::vec3 m_endPoint;
	glm::vec4 m_lineColor{ glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) };
	bool needInitialising = false;


};

