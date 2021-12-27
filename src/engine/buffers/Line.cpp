#include "Line.h"
#include <array>
#include "../maths/MatrixManager.h"
#include "../shaders/ShaderProgramManager.h"

Line::Line(glm::vec3 start, glm::vec3 end)
	: m_startPoint(start)
	, m_endPoint(end)
	, m_lineColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f))
	, m_vertices({ start.x, start.y, start.z, end.x, end.y, end.z })
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	setupBuffers();
}

Line::~Line()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Line::setupBuffers()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices) * m_vertices.size(), m_vertices.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Line::updateShader() {
	auto& matrixManager = MatrixManager::getInstance();
	auto& shaderProgramManager = ShaderProgramManager::getInstance();
	auto& laserProgram = shaderProgramManager.getShaderProgram("laser");

	laserProgram.useProgram();
	laserProgram.setUniform("matrices.projectionMatrix", matrixManager.getProjectionMatrix());
	laserProgram.setUniform("matrices.viewMatrix", matrixManager.getViewMatrix());
	laserProgram.setUniform("matrices.modelMatrix", glm::mat4(1.0f));
	laserProgram.setUniform("color", m_lineColor);
}
void Line::draw()
{
	updateShader();
	glBindVertexArray(m_VAO);
	glEnable(GL_LINE_WIDTH);
	GLfloat lineWidthRange[2];
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
	glLineWidth(static_cast<GLfloat>(lineWidthRange[1]));
	glDrawArrays(GL_LINES, 0, 2);
	glDisable(GL_LINE_WIDTH);
}
// where:
// linePoints -> start & end coords
bool Line::isColliding(std::array<glm::vec3, 2> linePoints, glm::vec3 sphereCoords, float radius)
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

void Line::setColor(const glm::vec4& color) {
	m_lineColor = color;
}

void Line::setPosition(const glm::vec3& start, const glm::vec3& end){
    m_startPoint = start;
    m_endPoint = end;

	m_vertices.clear();
	m_vertices.insert(m_vertices.end(), { start.x, start.y, start.z, end.x, end.y, end.z });
	setupBuffers();
}

glm::vec3 Line::getStartPosition() const {
    return m_startPoint;
}

glm::vec3 Line::getEndPosition() const {
    return m_endPoint;
}
