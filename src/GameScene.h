#pragma once
#include "../src/SetupWindow.h"
#include "../src/Shader.h"
#include "../src/ShaderProgram.h"
#include "../src/VBO.h"
class GameScene : public SetupWindow
{
public:
    void initScene() override;
    void renderScene() override;
    void updateScene() override;
    void releaseScene() override;
private:
    Shader m_vsShader, m_fsShader;
    ShaderProgram m_mainProgram;
    VBO m_VBOBuffer;
    GLuint m_VAO;
};

