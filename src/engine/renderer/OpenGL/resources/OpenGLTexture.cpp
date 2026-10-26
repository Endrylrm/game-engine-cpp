#include "engine/renderer/OpenGL/resources/OpenGLTexture.hpp"

OpenGLTexture::OpenGLTexture(GLuint texture, int width, int height)
    : texture(texture), size(width, height)
{
}

OpenGLTexture::~OpenGLTexture()
{
    if (is_valid())
    {
        glDeleteTextures(1, &texture);
        texture = 0;
    }
}

bool OpenGLTexture::is_valid() const
{
    return texture != 0;
}

Vector2DInt OpenGLTexture::get_size() const
{
    return size;
}

GLuint OpenGLTexture::get_native_handle() const
{
    return texture;
}
