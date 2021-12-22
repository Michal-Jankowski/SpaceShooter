#pragma once
#include <GLAD/glad.h>

enum class FilterOptions {
	MIN_FILTER_NEAREST,
	MIN_FILTER_BILINEAR,
	MIN_FILTER_NEAREST_MIPMAP,
	MIN_FILTER_BILINEAR_MIPMAP,
	MIN_FILTER_TRILINEAR,
	MAG_FILTER_NEAREST,
	MAG_FILTER_BILINEAR,
};
class Sampler
{
public:
	void create(bool repeat);
	void bind(int textureNumber = 0) const;
	~Sampler();
	void deleteSampler();
	void setFilterOptions(FilterOptions filterOption, GLenum pname) const;
	void setRepeat(bool repeat);
private:
	GLuint m_samplerID = 0;
	bool m_isCreated = false;
	bool m_repeat = false;

};

