#include "StencilOutline.h"
#include "../maths/MatrixManager.h"
#include "../shaders/ShaderProgramManager.h"
#include "../../game\models\Collectible.h"

StencilOutline::StencilOutline(GameObject* entity1, GameObject* entity2, glm::mat4 model, glm::vec4 color, glm::vec3 scale)
	: m_entity1(entity1)
	, m_entity2(entity2)
	, m_color(color)
	, m_model(model)
	, m_scale(scale)
{

}

void StencilOutline::update(SetupWindow* gScene) {

	GameObject::update(gScene);
}

void StencilOutline::render()
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	auto& matrixManager = MatrixManager::getInstance();
	auto& shaderProgramManager = ShaderProgramManager::getInstance();
	auto& mainProgram = shaderProgramManager.getShaderProgram("main");
	mainProgram.useProgram();
	mainProgram.setUniform("matrices.projectionMatrix", matrixManager.getProjectionMatrix());
	mainProgram.setUniform("matrices.viewMatrix", matrixManager.getViewMatrix());
	GameModel* entity = dynamic_cast<GameModel*>(m_entity1);
	// FIRST RENDER PASS
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", entity->transform->getMatrix());
	entity->mesh.render(entity->transform->getMatrix());
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	mainProgram.setUniform("isStencil", true);
	// Turning ON and OFF depth test causes weird depth glitches...bruh
	auto scaledModel = glm::scale(entity->transform->getMatrix(), glm::vec3(2, 2, 2));
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", scaledModel);
	glm::vec3 sc = entity->transform->getScale();
	entity->transform->setScale(glm::vec3(1.5, 1.5, 1.5));
	entity->mesh.render(entity->transform->getMatrix());
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	entity->transform->setScale(sc); // restore scale
	mainProgram.setUniform("isStencil", false);

	// SECOND RENDER PASS
}

bool StencilOutline::isValidCollisionTarget(GameObject* other) const {
	return false;
}

void StencilOutline::skip() const {
	glStencilMask(0x00);
}
