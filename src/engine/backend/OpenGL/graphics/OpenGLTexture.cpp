#include "engine/backend/OpenGL/graphics/OpenGLTexture.hpp"

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

GLuint OpenGLTexture::getNativeHandle() const
{
    return texture;
}

Vector2DInt OpenGLTexture::getSize() const
{
    return size;
}

bool OpenGLTexture::isValid() const
{
    return texture != 0;
}
