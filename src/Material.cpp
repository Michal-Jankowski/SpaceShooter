#include "Material.h"
#include "PathHelper.h"
#include "TextureManager.h"
#include "ShaderProgramManager.h"

Material::Material(const float intensity, const float strength, const bool isEnabled)
    : m_specularIntensity(intensity)
    , m_specularStrength(strength)
    , m_isEnabled(isEnabled)
{
}

Material& Material::none() {
    static Material noMaterial(0.0f, 0.0f, false);
    return noMaterial;
}

void Material::setUniform(ShaderProgram& shaderProgram, const std::string& uniformName) {
    shaderProgram.setUniform(constructAttributeName(uniformName, "isOn"), m_isEnabled);
    if (!m_isEnabled) {
        return;
    }
    shaderProgram.setUniform(constructAttributeName(uniformName, "specularIntensity"), m_specularIntensity);
    shaderProgram.setUniform(constructAttributeName(uniformName, "specularStrength"), m_specularStrength);
}

std::string Material::constructAttributeName(const std::string& uniformName, const std::string& attributeName) {
    return uniformName + "." + attributeName;
}

Material::Material(const aiMaterial *assimpMat) {
    generateMappings();

    aiString name;
    assimpMat->Get(AI_MATKEY_NAME,name);
    shaderProgramKey = materialShaderMappings[name.C_Str()];

    //TODO read spec params
    m_isEnabled = true;
    //m_specularIntensity =

    ///TEXUTRES
    aiString aiTexturePath;
    // TODO: this here is a hack for 64-bit system - Assimp has a problem extracting texture path apparently
    // On 64-bit version, some models report texture count 1 and then it crashes when getting them
    if (assimpMat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        if (assimpMat->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexturePath) == AI_SUCCESS)
        {
            const std::string textureFileName = aiStringToStdString(aiTexturePath);
            mainTextureKey = loadMaterialTexture(textureFileName);
        }
    }

}

std::string Material::loadMaterialTexture(const std::string &textureFileName) {
    // If the texture with such path is already loaded, just use it and go on
    const auto fullTexturePath = PathHelper::GetFullTexturePath(textureFileName);
    const auto newTextureKey = "assimp_" + fullTexturePath;

    const auto contains = TextureManager::getInstance().containsTexture(newTextureKey);
    if (!contains) {
        TextureManager::getInstance().loadTexture2D(newTextureKey, fullTexturePath);
    }
    return newTextureKey;
}
std::string Material::aiStringToStdString(const aiString& aiStringStruct)
{
    auto dataPtr = aiStringStruct.data;
    while (*dataPtr == 0) {
        dataPtr++;
    }

    return dataPtr;
}

void Material::generateMappings() {
    materialShaderMappings["DefaultMaterial"] = "";
    materialShaderMappings["main-ship"] = "main";
    materialShaderMappings["side-ship"] = "main";
}

std::string Material::getMainTextureKey() const {
    return mainTextureKey;
}
