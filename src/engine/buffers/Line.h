#pragma once
#include "../shaders/ShaderProgram.h"
#include <glm/glm.hpp>
class Line
{
public:
	Line(glm::vec3 start, glm::vec3 end);
	~Line();
	void draw();
	void setColor(const glm::vec4& color);
	void setPosition(const glm::vec3& start, const glm::vec3& end);
    [[nodiscard]] glm::vec3 getStartPosition() const;
    [[nodiscard]] glm::vec3 getEndPosition() const;
    [[nodiscard]] glm::vec3 getNormalisedDir() const;
private:
	void setupBuffers();
	void updateShader();
	unsigned int m_VBO{ 0 }, m_VAO{ 0 };
	std::vector<float> m_vertices;
    glm::vec3 m_startPoint;
    glm::vec3 m_endPoint;
	glm::vec4 m_lineColor;

	bool needInitialising = false;
};

