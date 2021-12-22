#pragma once
#include <glm/glm.hpp>
#include "../shaders/ShaderProgram.h"
#include "../models/procedural/Cube.h"

class Skybox : public Cube
{
public:
  Skybox(const std::string& path, bool withPositions, bool withTextureCoordinates, bool withNormals);
  ~Skybox();
  void render(const glm::vec3& position, ShaderProgram& shader) const;
  void loadTexture(const int sideBit) const;

   static const std::string SAMPLER_KEY;
private:
	static std::string getSideFileName(const int sideBit);
	std::string getTextureKey(const int sideBit) const;
	void tryLoadTexture(const int sideBit) const;
	
	std::string m_SkyboxDirectory;

};

