#pragma once
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <glad/gl.h>

#include "engine/core/math/Color.hpp"
#include "engine/core/math/Rect2D.hpp"
#include "engine/renderer/OpenGL/resources/OpenGLMesh.hpp"
#include "engine/renderer/OpenGL/resources/OpenGLShader.hpp"
#include "engine/renderer/RenderDevice.hpp"
#include "engine/renderer/resources/Texture.hpp"

class OpenGLDevice final : public RenderDevice
{
public:
    OpenGLDevice(SDL_Window *window_handle);
    ~OpenGLDevice() override;

    bool init() override;
    void clear(Color color) override;
    void present() override;
    void set_viewport(Rect2D rect) override;

    std::unique_ptr<Texture> create_texture(const std::string &path) override;

    void draw_texture(Texture *texture, Rect2D rect) override;
    void draw_rect(Rect2D rect, Color color) override;

private:
    bool init_glad();
    bool init_viewport();
    bool init_triangle_pipeline();
    bool init_rect_pipeline();
    bool init_texture_pipeline();
    bool init_open_gl_state();

    SDL_Window *window{};
    SDL_GLContext context{};

    OpenGLMesh texture_mesh;
    OpenGLShader texture_shader;

    OpenGLMesh triangle_mesh;
    OpenGLShader triangle_shader;

    OpenGLMesh rect_mesh;
    OpenGLShader rect_shader;
};
