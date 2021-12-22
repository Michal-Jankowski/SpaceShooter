#pragma once
#include "../Material.h"
#include "Sphere.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>

class Planet
{
public:
    Planet(const std::string& textureKey, Material& material,
        float radius, float distanceFromCenter, float orbitalPeriodDays, float rotationAngleSpeed, float initialOrbitAngle);

    void render() const;
    void renderPoints() const;
    void update();
    static void initializeGeometry(int slices, int stacks);
    static void freeGeometry();

private:
    static std::unique_ptr<Sphere> sphereMesh; // Sphere mesh

    std::string _textureKey; // Texture key used to render this planet
    Material& _material; // Material used

    float _radius; // Radius of the planet
    float _distanceFromCenter; // Distance from the center of solar system (from sun)

    float _travelAngleSpeed; // How fast planet orbits (in radians)
    float _rotationAngleSpeed; // How fast planet rotates around its axis (in radians)

    float _orbitAngle; // Current orbit angle
    float _rotationAngle; // Current rotation angle
    glm::mat4 getModelMatrix() const;
};

