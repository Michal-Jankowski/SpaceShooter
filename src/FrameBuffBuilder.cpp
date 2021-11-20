#include "FrameBuffBuilder.h"

FrameBuffBuilder& FrameBuffBuilder::createAndBind(GLsizei width, GLsizei height) {
	frameBuffer_ = std::make_unique<FrameBuff>();
	frameBuffer_->createAndBind(width, height);
	return *this;
}

FrameBuffBuilder& FrameBuffBuilder::withColorAttachment(GLenum internalFormat) {
	if (frameBuffer_) {
		frameBuffer_->withColorAttachment(internalFormat);
	}

	return *this;
}

FrameBuffBuilder& FrameBuffBuilder::withTextureColorAttachment(GLenum internalFormat) {
	if (frameBuffer_) {
		frameBuffer_->withTextureColorAttachment(internalFormat);
	}

	return *this;
}

FrameBuffBuilder& FrameBuffBuilder::withDepthAttachment(GLenum internalFormat) {
	if (frameBuffer_) {
		frameBuffer_->withDepthAttachment(internalFormat);
	}

	return *this;
}

std::unique_ptr<FrameBuff> FrameBuffBuilder::finishAndGetUnique() {
	if (frameBuffer_ == nullptr) {
		return nullptr;
	}

	return frameBuffer_->finishInitialization() ? std::move(frameBuffer_) : nullptr;
}

std::shared_ptr<FrameBuff> FrameBuffBuilder::finishAndGetShared() {
	if (frameBuffer_ == nullptr) {
		return nullptr;
	}

	return frameBuffer_->finishInitialization() ? std::move(frameBuffer_) : nullptr;
}
