#include "ObjPicker.h"
#include "../maths/MatrixManager.h"
#include "../shaders/ShaderProgramManager.h"
#include "../textures/TextureManager.h"
#include "FrameBuff.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../models/procedural/Sphere.h"
ObjPicker& ObjPicker::getInstance()
{
    static ObjPicker manager;
    return manager;
}

void ObjPicker::initialize()
{
    // Create framebuffer for picking models
    m_pickingFrameBuff.createFrameBufferWithColorAndDepthWithDefaultScreenSize();

    // Create occluder cube - we only need vertices positions here, no texture coordinates or normals
    m_occluderCube = std::make_unique<Cube>(true, false, false);

    // Add sphere mesh
    m_meshes.push_back(std::make_unique<Sphere>(4.0f, 20, 20));
    const glm::vec3 sphereOcclusionBoxSize{ 8.0f, 8.0f, 8.0f };

    // Create several pickable models on the scene
    m_objects.push_back(PickableObject{ glm::vec3(-75.0f, 6.0f, -75.0f), m_meshes[0].get(), sphereOcclusionBoxSize });
    m_objects.push_back(PickableObject{ glm::vec3(-35.0f, 6.0f, 55.0f), m_meshes[0].get(), sphereOcclusionBoxSize });
    m_objects.push_back(PickableObject{ glm::vec3(80.0f, 6.0f, -30.0f), m_meshes[0].get(), sphereOcclusionBoxSize });
}
void ObjPicker::release()
{
    m_occluderCube.reset();
    m_meshes.clear();
}

void ObjPicker::renderAllPickableObjects()
{
    const auto& mm = MatrixManager::getInstance();
    auto& singleColorShaderProgram = ShaderProgramManager::getInstance().getShaderProgram("outline");
    singleColorShaderProgram.useProgram();
    singleColorShaderProgram.setUniform("matrices.projectionMatrix", mm.getProjectionMatrix());
    singleColorShaderProgram.setUniform("matrices.viewMatrix", mm.getViewMatrix());
    singleColorShaderProgram.setUniform("color", glm::vec4(1.0f, 0.0f, 0.0f, 0.4f));

    const auto& tm = TextureManager::getInstance();
    auto& mainProgram = ShaderProgramManager::getInstance().getShaderProgram("main");
    mainProgram.useProgram();

    for (auto i = 0; i < static_cast<int>(m_objects.size()); i++)
    {
        const auto& object = m_objects.at(i);

        auto modelMatrix = glm::translate(glm::mat4(1.0f), object.position);
        modelMatrix = glm::rotate(modelMatrix, object.rotationAngleRad, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, object.getRenderScale());
        mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", modelMatrix);

        const auto color = m_selectedIndex == i ? glm::vec4(0.0f, 0.5f, 1.0f, 1.0f) : glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        mainProgram.setUniform("color", color);
        m_shinyMaterial.setUniform(mainProgram, "material");

        if (dynamic_cast<Sphere*>(object.meshPtr))
        {
            tm.getTexture("snow").bind();
        }
        object.meshPtr->render();
    }
}

void ObjPicker::updateAllPickableObjects(float deltaTime)
{
    for (auto i = 0; i < static_cast<int>(m_objects.size()); i++)
    {
        auto& object = m_objects.at(i);
        if (m_selectedIndex == i) {
            object.renderScaleAngleRad += deltaTime * 4.0f;
        }
        else
        {
            object.rotationAngleRad += deltaTime;
            object.renderScaleAngleRad = 0.0f;
        }
    }
}

void ObjPicker::renderInColorMode()
{
    const auto& mm = MatrixManager::getInstance();

    auto& singleColorShaderProgram = ShaderProgramManager::getInstance().getShaderProgram("outline");
    singleColorShaderProgram.useProgram();
    singleColorShaderProgram.setUniform("matrices.projectionMatrix", mm.getProjectionMatrix());
    singleColorShaderProgram.setUniform("matrices.viewMatrix", mm.getViewMatrix());
    singleColorShaderProgram.setUniform("color", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    for (auto i = 0; i < static_cast<int>(m_objects.size()); i++)
    {
        const auto& object = m_objects.at(i);

        const auto r = i & 0xFF;
        const auto g = (i >> 8) & 0xFF;
        const auto b = (i >> 16) & 0xFF;
        const auto fr = static_cast<float>(r) / 255.0f;
        const auto fg = static_cast<float>(g) / 255.0f;
        const auto fb = static_cast<float>(b) / 255.0f;
        singleColorShaderProgram.setUniform("color", glm::vec4(fr, fg, fb, 1.0f));

        auto modelMatrix = glm::translate(glm::mat4(1.0f), object.position);
        modelMatrix = glm::rotate(modelMatrix, object.rotationAngleRad, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, object.getRenderScale());
            // Pixel Perfect Collision
            //modelMatrix = glm::scale(modelMatrix, object.occlusionBoxSize);
            //singleColorShaderProgram.setUniform("matrices.modelMatrix", modelMatrix);
            //m_occluderCube->render();
            // end
            singleColorShaderProgram.setUniform("matrices.modelMatrix", modelMatrix);
            object.meshPtr->render();
    }
}

std::string ObjPicker::getSelectedObjectDescription() const
{
    if (m_selectedIndex >= static_cast<int>(m_objects.size())) {
        return "No object";
    }

    const auto& object = m_objects.at(m_selectedIndex);

    if (dynamic_cast<Sphere*>(object.meshPtr))
    {
        return "Sphere (ID #" + std::to_string(m_selectedIndex) + ")";
    }

    return "Unknown";
}

void ObjPicker::resizePickingFrameBuffer(int width, int height)
{
    m_pickingFrameBuff.resize(width, height);
    m_pickingFrameBuff.setFullViewport();
}

void ObjPicker::performObjectPicking(int x, int y)
{
    m_pickingFrameBuff.bindAsBothReadAndDraw();
    m_pickingFrameBuff.setFullViewport();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderInColorMode();
    const auto colorValues = FrameBuff::readColorValue(x, y); 
    const auto r = static_cast<int>(colorValues[0]);
    const auto g = static_cast<int>(colorValues[1]);
    const auto b = static_cast<int>(colorValues[2]);
    auto result = r | (g << 8) | (b << 16);
    m_selectedIndex = result;
}

void ObjPicker::copyColorToDefaultFrameBuffer() const
{
    m_pickingFrameBuff.copyColorToDefaultFrameBuffer();
}


