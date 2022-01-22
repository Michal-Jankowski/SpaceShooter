#pragma once
#include "../../engine/models/GameModel.h"

#include <memory>
class StencilOutline: public GameObject {
public:
	StencilOutline(SetupWindow* scene, GameObject* entity1, GameObject* entity2, glm::mat4 model, glm::vec4 color, glm::vec3 scale);
	void update() override;
	void render() override;
	bool isValidCollisionTarget(GameObject* other) const override;
	void skip() const;
private:
	GameObject* m_entity1 = nullptr;
	GameObject* m_entity2 = nullptr;
	glm::vec3 m_scale = glm::vec3(10.0f);
	glm::vec4 m_color = glm::vec4(1.0f);
	glm::mat4 m_model = glm::mat4(1.0f);
};