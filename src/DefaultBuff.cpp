#include "DefaultBuff.h"
#include "SetupWindow.h"

void DefaultBuff::bindAsBothReadAndDraw() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DefaultBuff::bindAsRead() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void DefaultBuff::bindAsDraw() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GLint DefaultBuff::getDepthBits() {
	GLint depthBits = -1;
	bindAsRead();
	glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, GL_DEPTH, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, &depthBits);
	return depthBits;
}

GLint DefaultBuff::getStencilBits() {
	GLint stencilBits = -1;
	bindAsRead();
	glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &stencilBits);
	return stencilBits;
}

void DefaultBuff::setFullViewport() {
	const auto screenWidth = SetupWindow::getDefaultWindow()->getScreenWidth();
	const auto screenHeight = SetupWindow::getDefaultWindow()->getScreenHeight();

	glViewport(0, 0, screenWidth, screenHeight);
}
