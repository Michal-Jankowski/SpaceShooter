#include "Line.h"
#include <array>
#include "../maths/MatrixManager.h"
#include "../shaders/ShaderProgramManager.h"

Line::Line(const std::vector<glm::vec3>& points)
	: m_vertices(points)
{
	setupBuffers();
}

Line::Line(const glm::vec3& start, const glm::vec3& end)
	: m_startPoint(start)
	, m_endPoint(end)
	, m_vertices({start, end})
{
	setupBuffers();
}

void Line::clearBuffer() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}
Line::~Line()
{
	clearBuffer();
}

void Line::setupBuffers()
{
	auto strideIdx = 0;
	for (const auto& point : m_vertices) {
		m_verticesIndicies.emplace_back(strideIdx);
		strideIdx += 1;
	}
	glCreateVertexArrays(1, &m_VAO);
	glCreateBuffers(1, &m_VBO);
	glNamedBufferStorage(m_VBO, sizeof(m_vertices) * m_vertices.size(), m_vertices.data(), GL_DYNAMIC_STORAGE_BIT);
	glCreateBuffers(1, &m_IBO);
	glNamedBufferStorage(m_IBO, sizeof(GLushort) * m_verticesIndicies.size(), m_verticesIndicies.data(), GL_DYNAMIC_STORAGE_BIT);

	glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, 3 * sizeof(float));
	glVertexArrayElementBuffer(m_VAO, m_IBO);

	glEnableVertexArrayAttrib(m_VAO, 0);
	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(m_VAO, 0, 0);

}

void Line::draw()
{
	auto& matrixManager = MatrixManager::getInstance();
	auto& shaderProgramManager = ShaderProgramManager::getInstance();
	auto& mainProgram = shaderProgramManager.getShaderProgram("main");

	mainProgram.useProgram();
	mainProgram.setUniform("matrices.projectionMatrix", matrixManager.getProjectionMatrix());
	mainProgram.setUniform("matrices.viewMatrix", matrixManager.getViewMatrix());
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", glm::mat4(1.0f));
	mainProgram.setUniform("laser.color", m_lineColor);
	mainProgram.setUniform("laser.isLaserOn", true);

	glBindVertexArray(m_VAO);
	int bufferSize;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	const auto drawSize = bufferSize / sizeof(GLushort);
	glDrawElements(GL_LINES, drawSize, GL_UNSIGNED_SHORT, 0);
	mainProgram.setUniform("laser.isLaserOn", false);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Line::setColor(const glm::vec4& color) {
	m_lineColor = color;
}

void Line::setColor(const glm::vec3& color) {
    m_lineColor = glm::vec4(color, 1.0f);
}

void Line::setMultiplePositions(const std::vector<glm::vec3>& start) {

	m_vertices.clear();
	m_vertices = start;
	clearBuffer();
	setupBuffers();
}

void Line::setPosition(const std::vector<glm::vec3>& points){
	if (points.empty()) {
		return;
	}
    m_startPoint = points[0];
    m_endPoint = points[1];

	m_vertices.clear();
	m_vertices = points;
	clearBuffer();
	setupBuffers();
}

glm::vec3 Line::getStartPosition() const {
    return m_startPoint;
}

glm::vec3 Line::getEndPosition() const {
    return m_endPoint;
}

glm::vec3 Line::getNormalisedDir() const {
    return glm::normalize(m_endPoint-m_startPoint);
}


