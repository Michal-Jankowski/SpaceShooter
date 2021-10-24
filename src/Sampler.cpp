#include "Sampler.h"
#include <iostream>
void Sampler::create() {
	if (m_isCreated) {
		return;
	}

	glGenSamplers(1, &m_samplerID);
	m_isCreated = true;
	setRepeat(true);
}

void Sampler::bind(int samplerUnit) const {
    if (!m_isCreated) {
        std::cerr << "Sampler was not yet created!" << std::endl;
        return;
    }
	glBindSampler(samplerUnit, m_samplerID);
}

Sampler::~Sampler() {
}

void Sampler::deleteSampler() {

	glDeleteSamplers(1, &m_samplerID);
}

void Sampler::setFilterOptions(FilterOptions filterOption) const {

    if (!m_isCreated) {
        std::cerr << "Sampler was not yet created!" << std::endl;
        return;
    }
    const GLenum pname = GL_TEXTURE_MIN_FILTER;
    GLint param = GL_NEAREST;
    switch (filterOption) {
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
        std::cerr << "Invalid texture filtering option!" << std::endl;
    }
        
    glSamplerParameteri(m_samplerID, pname, param);
}

void Sampler::setRepeat(bool repeat) const {

    if (!m_isCreated) {
        std::cerr << "Sampler was not yet created!" << std::endl;
        return;
    }
    GLint param = repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE;

    glSamplerParameteri(m_samplerID, GL_TEXTURE_WRAP_S, param);
    glSamplerParameteri(m_samplerID, GL_TEXTURE_WRAP_T, param);
}
