#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include <SDL3/SDL.h>
#include <glad/gl.h>

#include <engine/core/graphics/Renderer.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/core/math/Rect2D.hpp>

class OpenGLRenderer : public Renderer
{
public:
    OpenGLRenderer(SDL_Window *windowHandle);
    ~OpenGLRenderer() override;
    bool onInit() override;
    std::unique_ptr<Texture> loadTexture(const std::string &path) override;
    void drawTexture(Texture *texture, float x, float y) override;
    void drawTexture(Texture *texture, float x, float y, float w, float h) override;
    void drawTexture(Texture *texture, Rect2D rect) override;
    void drawRect(
        float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a
    ) override;
    void drawRect(Rect2D rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void clear() override;
    void present() override;

private:
    bool initGlad();
    bool initViewport();
    bool initTrianglePipeline();
    bool initQuadPipeline();
    bool initTexturePipeline();
    bool initOpenGLState();

    SDL_Window *window{};
    SDL_GLContext context{};
    GLuint vao{};
    GLuint vbo{};
    GLuint ebo{};
    GLuint shaderProgram{};
};
