#include "Skybox.h"
#include "TextureManager.h"
#include "SamplerManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <mutex>

const std::string Skybox::SAMPLER_KEY = "skybox";

Skybox::Skybox(const std::string& path, bool withPositions, bool withTextureCoordinates, bool withNormals)
    : Cube(withPositions, withTextureCoordinates, withNormals)
    , m_SkyboxDirectory(path) {

    tryLoadTexture(CUBE_FRONT_FACE);
    tryLoadTexture(CUBE_BACK_FACE);
    tryLoadTexture(CUBE_LEFT_FACE);
    tryLoadTexture(CUBE_RIGHT_FACE);
    tryLoadTexture(CUBE_TOP_FACE);
    tryLoadTexture(CUBE_BOTTOM_FACE);

    static std::once_flag prepareOnceFlag;

    std::call_once(prepareOnceFlag, []() {
        auto& sm = SamplerManager::getInstance();
        auto& sampler = sm.createSampler(SAMPLER_KEY, FilterOptions::MAG_FILTER_BILINEAR, FilterOptions::MIN_FILTER_TRILINEAR);
        sampler.setRepeat(false);
    });
}

Skybox::~Skybox() {
    auto& tm = TextureManager::getInstance();
    tm.deleteTexture(getTextureKey(CUBE_FRONT_FACE));
    tm.deleteTexture(getTextureKey(CUBE_BACK_FACE));
    tm.deleteTexture(getTextureKey(CUBE_LEFT_FACE));
    tm.deleteTexture(getTextureKey(CUBE_RIGHT_FACE));
    tm.deleteTexture(getTextureKey(CUBE_TOP_FACE));
    tm.deleteTexture(getTextureKey(CUBE_BOTTOM_FACE));
}

void Skybox::render(const glm::vec3& position, ShaderProgram& shader) const  {

    const auto frontKey = getTextureKey(CUBE_FRONT_FACE);
    const auto backKey = getTextureKey(CUBE_BACK_FACE);
    const auto leftKey = getTextureKey(CUBE_LEFT_FACE);
    const auto rightKey = getTextureKey(CUBE_RIGHT_FACE);
    const auto topKey = getTextureKey(CUBE_TOP_FACE);
    const auto bottomKey = getTextureKey(CUBE_BOTTOM_FACE);
    auto& tm = TextureManager::getInstance();
    const auto& sampler = SamplerManager::getInstance().getSampler(SAMPLER_KEY);
    sampler.bind();

    // Turn off depth mask (don't write to depth buffer)
    glDepthMask(GL_FALSE);

    // Enlarge default cube by some factor, that's not further then far clipping plane (100 is fine)
    auto skyboxModelMatrix = glm::translate(glm::mat4(1.0f), position);
    skyboxModelMatrix = glm::scale(skyboxModelMatrix, glm::vec3(900.0f, 900.0f, 900.0f));
    shader.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", skyboxModelMatrix);

    // Render front side if texture has been loaded
    if (tm.containsTexture(frontKey)) {
        tm.getTexture(frontKey).bind();
        renderFaces(CUBE_FRONT_FACE);
    }

    // Render back side if texture has been loaded
    if (tm.containsTexture(backKey)) {
        tm.getTexture(backKey).bind();
        renderFaces(CUBE_BACK_FACE);
    }

    // Render left side if texture has been loaded
    if (tm.containsTexture(leftKey)) {
        tm.getTexture(leftKey).bind();
        renderFaces(CUBE_LEFT_FACE);
    }

    // Render right side if texture has been loaded
    if (tm.containsTexture(rightKey)) {
        tm.getTexture(rightKey).bind();
        renderFaces(CUBE_RIGHT_FACE);
    }

    // Render top side if texture has been loaded
    if (tm.containsTexture(topKey)) {
        tm.getTexture(topKey).bind();
        renderFaces(CUBE_TOP_FACE);
    }

    // Render bottom side if texture has been loaded
    if (tm.containsTexture(bottomKey)) {
        tm.getTexture(bottomKey).bind();
        renderFaces(CUBE_BOTTOM_FACE);
    }
    // Turn the depth mask back on
    glDepthMask(GL_TRUE);
}

void Skybox::loadTexture(const int sideBit) const {
}

std::string Skybox::getSideFileName(const int sideBit) {
    if (sideBit & CUBE_FRONT_FACE) {
        return "front";
    }
    else if (sideBit & CUBE_BACK_FACE) {
        return "back";
    }
    else if (sideBit & CUBE_LEFT_FACE) {
        return "left";
    }
    else if (sideBit & CUBE_RIGHT_FACE) {
        return "right";
    }
    else if (sideBit & CUBE_TOP_FACE) {
        return "top";
    }

    return "bottom";
}

std::string Skybox::getTextureKey(const int sideBit) const {
    return m_SkyboxDirectory + "/" + getSideFileName(sideBit);
}

void Skybox::tryLoadTexture(const int sideBit) const {
    const auto key = getTextureKey(sideBit);
    const auto fileName = key + ".png";
    try
    {
        auto& tm = TextureManager::getInstance();
        tm.loadTexture2D(key, fileName);
    }
    catch (const std::runtime_error&) {}
}
