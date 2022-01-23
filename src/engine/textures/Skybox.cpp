#include "Skybox.h"
#include "TextureManager.h"
#include "SamplerManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <mutex>
#include "../shaders/ShaderProgramManager.h"
#include "../maths/MatrixManager.h"
constexpr auto skyboxKey = "skybox";
constexpr auto skyboxBlueNight = "./res/skybox/blue/";


constexpr GLfloat skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f, // 0
    -1.0f, -1.0f, -1.0f, // 1
     1.0f, -1.0f, -1.0f, // 2
     1.0f,  1.0f, -1.0f, // 3
    -1.0f, -1.0f,  1.0f, // 4
    -1.0f,  1.0f,  1.0f, // 5
     1.0f, -1.0f,  1.0f, // 6
     1.0f,  1.0f,  1.0f, // 7 
};

constexpr GLushort skyboxIndices[] = {
    0, 1, 2,
    2, 3, 0,
    4, 1, 0,
    0, 5, 4,
    2, 6, 7,
    7, 3, 2,
    4, 5, 7,
    7, 6, 4,
    0, 3, 7,
    7, 5, 0,
    1, 4, 2,
    2, 4, 6,
};

Skybox::Skybox(const std::string& path)
    : m_SkyboxDirectory(path) {

    start();
   
}

void Skybox::start() {

  glGenVertexArrays(1, &skyboxVAO);
  glBindVertexArray(skyboxVAO);
  glGenBuffers(1, &skyboxVBO);
  glGenBuffers(1, &skyboxEBO);
  glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);

  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void*>(0));


  auto& tm = TextureManager::getInstance();
  tm.loadCubemap(skyboxKey, skyboxBlueNight);
  auto& smm = SamplerManager::getInstance();
  auto& sampler = smm.createSampler(skyboxKey, FilterOptions::MAG_FILTER_NEAREST, FilterOptions::MIN_FILTER_NEAREST);
  sampler.setRepeat(false);
  auto& shaderProgramManager = ShaderProgramManager::getInstance();
  auto& skyboxProgram = shaderProgramManager.getShaderProgram("skybox");
  skyboxProgram.useProgram();
  skyboxProgram.setUniform("skybox", 0);

}


Skybox::~Skybox() {
    auto& tm = TextureManager::getInstance();
    tm.deleteTexture(skyboxKey);  
}


void Skybox::render(const glm::vec3& position, ShaderProgram& shader) const  {

    auto& shaderProgramManager = ShaderProgramManager::getInstance();
    auto& skyboxProgram = shaderProgramManager.getShaderProgram("skybox");
    auto& matrixManager = MatrixManager::getInstance();
    const auto& sampler = SamplerManager::getInstance().getSampler(skyboxKey);
    sampler.bind();
    auto& tm = TextureManager::getInstance();
    glDepthFunc(GL_LEQUAL);
    skyboxProgram.useProgram();
    auto viewMatrix = glm::mat4(glm::mat3(matrixManager.getViewMatrix()));
    skyboxProgram.setUniform("matrices.modelMatrix", glm::mat4(1.0f));
    skyboxProgram.setUniform("matrices.viewMatrix", viewMatrix);
    skyboxProgram.setUniform("matrices.projectionMatrix", matrixManager.getProjectionMatrix());

    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tm.getTexture("skybox").getID());
    int bufferSize;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    const auto drawSize = bufferSize / sizeof(GLushort);
    glDrawElements(GL_TRIANGLES, drawSize, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
}
