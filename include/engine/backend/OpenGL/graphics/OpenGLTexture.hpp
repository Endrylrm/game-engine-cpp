#pragma once
#include <cstdint>
#include <string>

#include <SDL3/SDL.h>
#include <glad/gl.h>

#include <engine/core/graphics/Texture.hpp>
#include <engine/core/math/Vector2DInt.hpp>

class OpenGLTexture : public Texture
{
public:
    OpenGLTexture(GLuint texture, int width, int height);
    ~OpenGLTexture() override;

    GLuint getNativeHandle() const;

    Vector2DInt getSize() const override;

    bool isValid() const override;

private:
    GLuint texture{};
    Vector2DInt size{};
};
