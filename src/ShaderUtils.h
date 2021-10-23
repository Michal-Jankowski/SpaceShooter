#pragma once
#include <string>

#define SHADER_CONSTANT(constantName, constantValue) \
static const std::string constantName() {            \
    static std::string value = constantValue;        \
    return value;                                    \
}

#define SHADER_CONSTANT_INDEX(constantName, constantValue)               \
SHADER_CONSTANT(constantName, constantValue)                             \
static const std::string constantName(const int idx) {                   \
    return std::string(constantValue) + "[" + std::to_string(idx) + "]"; \
}

class ShaderConstants
{
public:
    // Matrices
    SHADER_CONSTANT(viewMatrix, "matrices.viewMatrix");
    // Colour & textures
    SHADER_CONSTANT(color, "color");
    //Lighting
    SHADER_CONSTANT(ambientLight, "ambientLight");
};
