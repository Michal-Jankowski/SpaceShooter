#pragma once
#include <memory>
#include <thread>
#include <deque>
#include <mutex>

#include "../engine/core/SetupWindow.h"
#include "elements/Camera.h"
#include "../engine/models/GameModel.h"
#include "../engine/textures/Skybox.h"
#include "../engine/lighting/DiffuseLight.h"
#include "../engine/lighting/AmbientLight.h"
#include "../engine/models/procedural/PlainGround.h"
#include "../engine/buffers/Line.h"
#include "../engine/models/procedural/Sphere.h"
#include <queue>

class GameScene : public SetupWindow
{
public:
    void initScene() override;
    void renderScene() override;
    void updateScene() override;
    void releaseScene() override;
    void onWindowSizeChanged(int width, int height) override;
    void onMouseButtonPressed(int button, int action) override;
    void addObject(std::unique_ptr<GameObject> gameObjet);
private:
    void gameObjectsLoop();
    void drawGameObjectsHUD();
    void updateMatrices();
    void updateShaderMatrices(const std::string &shaderKey);
    void updateLights(const std::string &shaderKey);
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    std::queue<std::unique_ptr<GameObject>> creatingGameObjects;
    std::shared_ptr<Camera> m_camera;
    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<Cube> m_cube;
    std::unique_ptr<AmbientLight> m_ambientLight;
    std::unique_ptr<DiffuseLight> m_diffuseLight;
    std::unique_ptr<Material> m_material;
    std::unique_ptr<Sphere> m_sphere;
    std::unique_ptr<GameHUD> m_HUD;
    float m_rotationAngleRad = 0.0f;
};

