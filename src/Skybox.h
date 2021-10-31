#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"

class Skybox
{
  Skybox(const std::string& path);
  ~Skybox();
  void render(const glm::vec3& position, ShaderProgram& shader) const;
  void loadTexture(const int sideBit) const;
};

