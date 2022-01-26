

#ifndef SPACESHOOTER_SUN_H
#define SPACESHOOTER_SUN_H


#include "Planet.h"
#include "../../engine/lighting/PointLight.h"

class Sun : public Planet {
public:
    Sun(SetupWindow* scene,
    float size,
    const glm::vec3& position, PointLight* pointLightRef, float orbit, float orbitSpeed);
    void update() override;

private:
    float orbit;
    float orbitSpeed;
    float size;
    glm::vec3 initPos;
    PointLight* pointLightRef;
    inline static const std::string MODEL_PATH = "../res/models/sun.obj";
};


#endif //SPACESHOOTER_SUN_H
