#pragma once
#include <glm/glm.hpp>
#include "../../lighting/pointLight/PointLight.h"

class MovingPointLight : public PointLight
{
public:
	MovingPointLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, const float ambientFactor, const float constantAtt,
		const float linearAtt, const float expAtt, const bool isOn = true)
		: PointLight(position, color, ambientFactor, constantAtt, linearAtt, expAtt, isOn)
		, direction(direction) {}
	void update(const float moveBy, const float y);
	static MovingPointLight createRandomPointLight(glm::vec3 position, glm::vec3 direction);
	static const double MAX_TRAVEL_DISTANCE;
	glm::vec3 direction;


};

