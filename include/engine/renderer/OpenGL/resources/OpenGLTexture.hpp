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

    bool is_valid() const override;

    Vector2DInt get_size() const override;
    GLuint get_native_handle() const;

private:
    GLuint texture{};
    Vector2DInt size{};
};
