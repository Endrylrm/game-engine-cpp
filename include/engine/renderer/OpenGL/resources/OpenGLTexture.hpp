#pragma once
#include "engine/core/math/Vector2DInt.hpp"
#include "engine/renderer/resources/Texture.hpp"

#include <cstdint>
#include <string>

#include <SDL3/SDL.h>
#include <glad/gl.h>

class OpenGLTexture final : public Texture
{
public:
    OpenGLTexture(GLuint texture, int width, int height);
    ~OpenGLTexture() override;

    bool isValid() const override;

    Vector2DInt getSize() const override;
    GLuint getNativeHandle() const;

private:
    GLuint texture{};
    Vector2DInt size{};
};
