#include "SamplerManager.h"

SamplerManager& SamplerManager::getInstance() {
	static SamplerManager samplerManager;
	return samplerManager;
}

Sampler& SamplerManager::createSampler(const std::string& key, const FilterOptions magnificationFilter, const FilterOptions minificationFilter) {
    if (containsSampler(key)) {
        const auto msg = "Sampler with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }

    std::unique_ptr<Sampler> sampler = std::make_unique<Sampler>();
    sampler->create(true);
    sampler->bind();
    sampler->setFilterOptions(magnificationFilter, GL_TEXTURE_MAG_FILTER);
    sampler->setFilterOptions(minificationFilter, GL_TEXTURE_MIN_FILTER);
    m_samplerKeys[key] = std::move(sampler);

    return getSampler(key);
}

Sampler& SamplerManager::getSampler(const std::string& key) const {
    if (!containsSampler(key))
    {
        const auto msg = "Attempting to get non-existing sampler with key '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }

    return *m_samplerKeys.at(key);
}

void SamplerManager::clearSamplerKeys() {
    m_samplerKeys.clear();
}

bool SamplerManager::containsSampler(const std::string& key) const {
    return m_samplerKeys.count(key) > 0;
}
