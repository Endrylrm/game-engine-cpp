#pragma once
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <glad/gl.h>

#include <engine/core/graphics/Renderer.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/core/math/Color.hpp>
#include <engine/core/math/Rect2D.hpp>
#include <engine/core/math/Vector2D.hpp>

#include "OpenGLMesh.hpp"
#include "OpenGLShader.hpp"

class OpenGLRenderer final : public Renderer
{
public:
    OpenGLRenderer(SDL_Window *windowHandle);
    ~OpenGLRenderer() override;
    bool onInit() override;
    std::unique_ptr<Texture> loadTexture(const std::string &path) override;
    void drawTexture(Texture *texture, Vector2D position) override;
    void drawTexture(Texture *texture, Vector2D position, Vector2D size) override;
    void drawTexture(Texture *texture, Rect2D rect) override;
    void drawRect(Vector2D position, Vector2D size, Color color) override;
    void drawRect(Rect2D rect, Color color) override;
    void clear() override;
    void present() override;

private:
    bool initGlad();
    bool initViewport();
    bool initTrianglePipeline();
    bool initRectPipeline();
    bool initTexturePipeline();
    bool initOpenGLState();

    SDL_Window *window{};
    SDL_GLContext context{};

    OpenGLMesh textureMesh;
    OpenGLShader textureShader;

    OpenGLMesh triangleMesh;
    OpenGLShader triangleShader;

    OpenGLMesh rectMesh;
    OpenGLShader rectShader;
};
