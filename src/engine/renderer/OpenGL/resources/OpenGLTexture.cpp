#include "engine/renderer/OpenGL/resources/OpenGLTexture.hpp"

OpenGLTexture::OpenGLTexture(GLuint texture, int width, int height)
    : texture(texture), size(width, height)
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

bool OpenGLTexture::isValid() const
{
    return texture != 0;
}

Vector2DInt OpenGLTexture::getSize() const
{
    return size;
}

GLuint OpenGLTexture::getNativeHandle() const
{
    return texture;
}
