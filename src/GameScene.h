#pragma once
#include "../src/SetupWindow.h"
#include "../src/Shader.h"
#include "../src/ShaderProgram.h"
#include "../src/VBO.h"
#include "../src/TextureLoader.h"
#include "../src/Sampler.h"
#include "../src/StaticMesh.h"
#include "../src/Camera.h"
#include <memory>
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
    VBO m_vertexBuffer, m_textureBuffer;
    StaticMesh m_staticGeometry;
    GLuint m_VAO;
};

