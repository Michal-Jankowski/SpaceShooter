#pragma once
#include "Sampler.h"
#include <string>
#include <map>
#include <memory>
#include <stdexcept>

class SamplerManager {

public:
	static SamplerManager& getInstance();
	Sampler& createSampler(const std::string& key, const FilterOptions magnificationFilter, const FilterOptions minificationFilter);
	Sampler& getSampler(const std::string& key) const;
	void clearSamplerKeys();
private:
	SamplerManager() {}
	SamplerManager(const SamplerManager&) = delete;
	void operator=(const SamplerManager&) = delete;
	bool containsSampler(const std::string& key) const;
	std::map<std::string, std::unique_ptr<Sampler>> m_samplerKeys;
};