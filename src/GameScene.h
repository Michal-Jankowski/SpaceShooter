#pragma once
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
    Sampler m_sampler;
    std::unique_ptr<Camera> m_camera;
    Buffer m_vertexBuffer, m_textureBuffer, m_vertexEBO;
    StaticMesh m_staticGeometry;
    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<Cube> m_cube;
    std::unique_ptr<AmbientLight> m_ambientLight;
    std::unique_ptr <DiffuseLight> m_diffuseLight;
    std::unique_ptr<PlainGround> m_plainGround;
    GLuint m_VAO;
    GLuint m_EBO;
};

