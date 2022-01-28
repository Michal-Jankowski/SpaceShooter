#pragma once
#include <glm/glm.hpp>
#include "../shaders/ShaderProgram.h"
#include "../models/procedural/Cube.h"
#include "../utils/Buffer.h"


class Skybox : public Cube
{
public:
  Skybox(const std::string& path);
  ~Skybox();
  void render(const glm::vec3& position, ShaderProgram& shader) const;
private:
	void start();
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	std::string m_SkyboxDirectory;

};

