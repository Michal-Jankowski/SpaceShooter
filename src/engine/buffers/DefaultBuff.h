#pragma once
#include "GLAD/glad.h"

class DefaultBuff
{
public:
    static void bindAsBothReadAndDraw();
    static void bindAsRead();
    static void bindAsDraw();
    static GLint getDepthBits();
    static GLint getStencilBits();
    static void setFullViewport();
};

