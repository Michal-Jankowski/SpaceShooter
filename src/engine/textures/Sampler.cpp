#include "Sampler.h"
#include <iostream>
void Sampler::create(bool repeat) {
	if (m_isCreated) {
		return;
	}

	glGenSamplers(1, &m_samplerID);
	m_isCreated = true;
    m_repeat = repeat;
	setRepeat(m_repeat);
}

void Sampler::bind(int textureUnit) const {
    if (!m_isCreated) {
        std::cerr << "ERROR: Create sampler first!" << std::endl;
        return;
    }
	glBindSampler(textureUnit, m_samplerID);
}

Sampler::~Sampler() {
    deleteSampler();
}

void Sampler::deleteSampler() {

	glDeleteSamplers(1, &m_samplerID);
}

void Sampler::setFilterOptions(FilterOptions filterOption, GLenum pname) const {

    if (!m_isCreated) {
        std::cerr << "ERROR: Create sampler first!" << std::endl;
        return;
    }
    GLint param = GL_NEAREST;
    switch (filterOption) {
    case FilterOptions::MIN_FILTER_NEAREST:
        param = GL_NEAREST;
        break;
    case FilterOptions::MIN_FILTER_BILINEAR:
        param = GL_LINEAR;
        break;
    case FilterOptions::MIN_FILTER_NEAREST_MIPMAP:
        param = GL_NEAREST_MIPMAP_NEAREST;
        break;
    case FilterOptions::MIN_FILTER_BILINEAR_MIPMAP:
        param = GL_LINEAR_MIPMAP_NEAREST;
        break;
    case FilterOptions::MIN_FILTER_TRILINEAR:
        param = GL_LINEAR_MIPMAP_LINEAR;
        break;
    case FilterOptions::MAG_FILTER_NEAREST:
        param = GL_NEAREST;
        break;
    case FilterOptions::MAG_FILTER_BILINEAR:
        param = GL_LINEAR;
        break;
    default:
        throw std::runtime_error("Invalid texture filtering option!");
    }
        
    glSamplerParameteri(m_samplerID, pname, param);
}

void Sampler::setRepeat(bool repeat) {

    if (!m_isCreated) {
        std::cerr << "ERROR: Create sampler first!" << std::endl;
        return;
    }
    m_repeat = repeat;
    GLint param = m_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE;

    glSamplerParameteri(m_samplerID, GL_TEXTURE_WRAP_S, param);
    glSamplerParameteri(m_samplerID, GL_TEXTURE_WRAP_T, param);
}
