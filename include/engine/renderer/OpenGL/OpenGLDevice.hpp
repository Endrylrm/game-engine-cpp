#pragma once
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <glad/gl.h>

#include <engine/core/math/Color.hpp>
#include <engine/core/math/Rect2D.hpp>
#include <engine/renderer/OpenGL/resources/OpenGLMesh.hpp>
#include <engine/renderer/OpenGL/resources/OpenGLShader.hpp>
#include <engine/renderer/RenderDevice.hpp>
#include <engine/renderer/resources/Texture.hpp>

class OpenGLDevice final : public RenderDevice
{
public:
    OpenGLDevice(SDL_Window *windowHandle);
    ~OpenGLDevice() override;

    bool init() override;
    void clear(Color color) override;
    void present() override;
    void setViewport(Rect2D rect) override;

    std::unique_ptr<Texture> createTexture(const std::string &path) override;

    void drawTexture(Texture *texture, Rect2D rect) override;
    void drawRect(Rect2D rect, Color color) override;

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
