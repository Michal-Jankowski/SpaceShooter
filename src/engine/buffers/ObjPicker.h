#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "../models/procedural/StaticMesh3D.h"
#include "FrameBuff.h"
#include "../models/Material.h"
#include "../models/procedural/Cube.h"


class ObjPicker {
public:
    static ObjPicker& getInstance();

    void initialize();
    void release();
    void renderAllPickableObjects();
    void updateAllPickableObjects(float deltaTime);
    bool isPixelPerfectSelectionMode() const;
    void performObjectPicking(int x, int y);
    void copyColorToDefaultFrameBuffer() const;
    std::string getSelectedObjectDescription() const;
    void resizePickingFrameBuffer(int width, int height);

private:
    ObjPicker() = default; 
    ObjPicker(const ObjPicker&) = delete; 
    void operator=(const ObjPicker&) = delete;

    struct PickableObject
    {
        glm::vec3 position;
        StaticMesh3D* meshPtr;
        glm::vec3 occlusionBoxSize;
        float rotationAngleRad{ 0.0f };
        float renderScaleAngleRad{ 0.0f };


        // Creates pulsing effect with sine method.
        glm::vec3 getRenderScale() const
        {
            const auto sine = sin(renderScaleAngleRad);
            const auto scaleFactor = 1.0f + sine * 0.1f;
            return glm::vec3{ scaleFactor };
        }
    };

    void renderInColorMode();

    std::unique_ptr<Cube> m_occluderCube; 
    std::vector<std::unique_ptr<StaticMesh3D>> m_meshes;
    std::vector<PickableObject> m_objects; 

    FrameBuff m_pickingFrameBuff; 
    int m_selectedIndex{ std::numeric_limits<int>::max() }; 

    Material m_shinyMaterial{ 1.0f, 32.0f }; 

};

