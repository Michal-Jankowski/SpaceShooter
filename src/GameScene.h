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
    //std::unique_ptr<Skybox> m_skybox;
    GLuint m_VAO;
    GLuint m_EBO;
};

