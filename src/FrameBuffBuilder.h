#pragma once
#include <GLAD/glad.h>
#include <memory>
#include "FrameBuff.h"
class FrameBuffBuilder 
{
public:
	FrameBuffBuilder& createAndBind(GLsizei width, GLsizei height);
	FrameBuffBuilder& withColorAttachment(GLenum internalFormat);
	FrameBuffBuilder& withTextureColorAttachment(GLenum internalFormat);
	FrameBuffBuilder& withDepthAttachment(GLenum internalFormat);
	std::unique_ptr<FrameBuff> finishAndGetUnique();
	std::shared_ptr<FrameBuff> finishAndGetShared();

private:
	std::unique_ptr<FrameBuff> frameBuffer_; // Holds framebuffer that is being built


};