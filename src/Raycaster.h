#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Mesh.h"
#include "FrameBuff.h"
#include "Material.h"
#include "Cube.h"

struct PickableObject
{
    glm::vec3 position; 
    Mesh* meshPtr;
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

class Raycaster {
public:
    static Raycaster& getInstance();

    void initialize();
    void release();
    void renderAllPickableObjects();
    void updateAllPickableObjects(float deltaTime);
    bool isPixelPerfectSelectionMode() const;
    void togglePixelPerfectSelectionMode();
    void performObjectPicking(int x, int y);
    void copyColorToDefaultFrameBuffer() const;
    std::string getSelectedObjectDescription() const;
    void resizePickingFrameBuffer(int width, int height);

private:
    Raycaster() = default; 
    Raycaster(const Raycaster&) = delete; 
    void operator=(const Raycaster&) = delete;

    void renderInColorMode();

    std::unique_ptr<Cube> occluderCube_; 
    std::vector<std::unique_ptr<Mesh>> meshes_; 
    std::vector<PickableObject> objects_; 

    FrameBuff pickingFrameBuffer_; 
    bool pixelPerfectSelectionMode_{ true }; 
    int selectedIndex_{ std::numeric_limits<int>::max() }; 

    Material shinyMaterial_{ 1.0f, 32.0f }; 

};

