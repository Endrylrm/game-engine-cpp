#pragma once
#include <memory>
#include <string>

#include "engine/core/math/Color.hpp"
#include "engine/renderer/RenderDevice.hpp"
#include "engine/renderer/resources/Texture.hpp"

#include "ShapeRenderer.hpp"
#include "SpriteRenderer.hpp"

class Renderer
{
public:
    bool init(RenderDevice *newDevice);

    std::unique_ptr<Texture> loadTexture(const std::string &path);

    ShapeRenderer &getShapeRenderer() noexcept;
    SpriteRenderer &getSpriteRenderer() noexcept;

    void clear();
    void setClearColor(Color color);

    void present();

private:
    RenderDevice *device = nullptr;
    ShapeRenderer shapeRenderer;
    SpriteRenderer spriteRenderer;
    Color clearColor{0.0f, 0.0f, 0.0f, 1.0f};
};
