#pragma once
#include "../src/SetupWindow.h"
#include "../src/Shader.h"
#include "../src/ShaderProgram.h"
#include "../src/Buffer.h"
#include "../src/TextureLoader.h"
#include "../src/Sampler.h"
#include "../src/StaticMesh.h"
#include "../src/Camera.h"
#include "ModelMesh.h"
#include <memory>
#include "../src/Skybox.h"
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

class GameScene : public SetupWindow
{
public:
    void initScene() override;
    void renderScene() override;
    void updateScene() override;
    void releaseScene() override;
private:
    Shader m_vsShader, m_fsShader, m_vsGround, m_fsGround;
    ShaderProgram m_mainProgram, m_groundProgram;
    TextureLoader m_snowTexture;
    ModelMesh m_ship;
    Sampler m_sampler;
    std::unique_ptr<Camera> m_camera;
    Buffer m_vertexBuffer, m_textureBuffer, m_vertexEBO;
    StaticMesh m_staticGeometry;
    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<Cube> m_cube;
    std::unique_ptr<AmbientLight> m_ambientLight;
    std::unique_ptr<DiffuseLight> m_diffuseLight;
    std::unique_ptr<PlainGround> m_plainGround;
    std::unique_ptr<Material> m_material;
    GLuint m_VAO;
    GLuint m_EBO;
};

