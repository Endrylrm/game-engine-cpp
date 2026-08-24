#pragma once
#include <cstdint>
#include <string>

#include <SDL3/SDL.h>
#include <glad/gl.h>

#include <engine/core/graphics/Texture.hpp>

class OpenGLTexture : public Texture
{
public:
    OpenGLTexture(GLuint texture, int width, int height);
    ~OpenGLTexture() override;

    GLuint getNativeHandle() const;

    int getWidth() const override;
    int getHeight() const override;

    bool isValid() const override;

private:
    GLuint texture{};
    int width{};
    int height{};
};
