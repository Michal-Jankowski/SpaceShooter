#pragma once
#include "ModelMesh.h"
#include <memory>
#include "SetupWindow.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "TextureLoader.h"
#include "Sampler.h"
#include "StaticMesh.h"
#include "Camera.h"
#include "Skybox.h"
#include "AmbientLight.h"
#include "DiffuseLight.h"
#include "PlainGround.h"
#include "Material.h"
#include "GameModel.h"
#include <thread>
#include <deque>
#include <mutex>
#include "Laser.h"

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
    std::unique_ptr<GameModel> m_ship;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<Cube> m_cube;
    std::unique_ptr<AmbientLight> m_ambientLight;
    std::unique_ptr<DiffuseLight> m_diffuseLight;
    std::unique_ptr<PlainGround> m_plainGround;
    std::unique_ptr<Material> m_material;
    std::unique_ptr<Laser> m_raycast;
    float m_rotationAngleRad = 0.0f;
};

