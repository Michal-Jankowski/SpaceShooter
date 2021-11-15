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
#include "game/Ship.h"
#include "game/Collectible.h"

class GameScene : public SetupWindow
{
public:
    void initScene() override;
    void renderScene() override;
    void updateScene() override;
    void releaseScene() override;
private:
    std::vector<std::unique_ptr<GameModel>> gameObjects;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<Cube> m_cube;
    std::unique_ptr<AmbientLight> m_ambientLight;
    std::unique_ptr<DiffuseLight> m_diffuseLight;
    std::unique_ptr<PlainGround> m_plainGround;
    std::unique_ptr<Material> m_material;
    float m_rotationAngleRad = 0.0f;
};

