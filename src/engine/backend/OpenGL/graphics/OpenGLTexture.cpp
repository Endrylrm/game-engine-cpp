#include "engine/backend/OpenGL/graphics/OpenGLTexture.hpp"

OpenGLTexture::OpenGLTexture(GLuint texture, int width, int height)
    : texture(texture), width(width), height(height)
{
}

OpenGLTexture::~OpenGLTexture()
{
    if (isValid())
    {
        glDeleteTextures(1, &texture);
        texture = 0;
    }
}

GLuint OpenGLTexture::getNativeHandle() const
{
    return texture;
}

int OpenGLTexture::getWidth() const
{
    return width;
}

int OpenGLTexture::getHeight() const
{
    return height;
}

bool OpenGLTexture::isValid() const
{
    return texture != 0;
}
