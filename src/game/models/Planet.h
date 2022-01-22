

#ifndef SPACESHOOTER_PLANET_H
#define SPACESHOOTER_PLANET_H

#include "../../engine/models/GameModel.h"

class Planet : public GameModel 
{
public:
    Planet(SetupWindow* scene,
            float size,
            bool generateSurroundings,
            const glm::vec3& position = glm::vec3(0));
    Planet(SetupWindow* scene,
            float size,
            bool generateSurroundings,
            const std::string &modelPath,
            const glm::vec3& position = glm::vec3(0));
    void update() override;
    void render() override;
    void onCollision(GameObject* other) override;
    bool isValidCollisionTarget(GameObject* other) const override;
private:
    inline static const std::string MODEL_PATH = "../res/models/planet.obj";

    int enemies = 10;
    int collectibles = 1;
    float collectiblesOffset = 1.1f;
    float turretsOffset = 1.1f;
    float minesOffset = 1.0f;
    float mineToTurretRatio = 0.5f;
};


#endif //SPACESHOOTER_PLANET_H
