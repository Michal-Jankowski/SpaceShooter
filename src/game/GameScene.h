#pragma once

#include <memory>
#include <thread>
#include <deque>
#include <mutex>

#include "../engine/core/SetupWindow.h"
#include "../engine/core/Camera.h"
#include "../engine/models/GameModel.h"
#include "../engine/textures/Skybox.h"
#include "../engine/lighting/DiffuseLight.h"
#include "../engine/lighting/AmbientLight.h"
#include "../engine/models/procedural/PlainGround.h"
#include "../engine/buffers/Laser.h"
#include "../engine/models/procedural/Sphere.h"
#include "UI/GameHUD.h"
#include "../engine/lighting/pointLight/PointLight.h"
#include "../engine/lighting/pointLight/MovingPointLight.h"
#include "../engine/buffers/UniformBufferObject.h"

class GameScene : public SetupWindow
{
public:
    void initScene() override;
    void renderScene() override;
    void updateScene() override;
    void releaseScene() override;
    void onWindowSizeChanged(int width, int height) override;
    void onMouseButtonPressed(int button, int action) override;
private:
    void gameObjectsLoop();
    std::vector<std::unique_ptr<GameModel>> gameObjects;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<Cube> m_cube;
    std::unique_ptr<AmbientLight> m_ambientLight;
    std::unique_ptr<DiffuseLight> m_diffuseLight;
    std::unique_ptr<PlainGround> m_plainGround;
    std::unique_ptr<Material> m_material;
    std::unique_ptr<Laser> m_raycast;
    std::unique_ptr<Sphere> m_sphere;
    std::unique_ptr<GameHUD> m_HUD;
    std::unique_ptr<UniformBufferObject> m_UBOMatrices;
    std::unique_ptr<UniformBufferObject> m_UBOPointLights;
    std::deque<MovingPointLight> m_pointLights;
    float m_rotationAngleRad = 0.0f;
    const int MAX_POINT_LIGHTS = 5;
};

