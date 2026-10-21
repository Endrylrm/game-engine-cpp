#pragma once
#include "engine/core/math/Color.hpp"
#include "engine/core/math/Rect2D.hpp"
#include "engine/core/math/Vector2D.hpp"
#include "engine/renderer/RenderDevice.hpp"
#include "engine/renderer/resources/Texture.hpp"

class SpriteRenderer
{
public:
    void init(RenderDevice *newDevice);

    void drawTexture(Texture *texture, Vector2D position);
    void drawTexture(Texture *tex, Vector2D position, Vector2D size);
    void drawTexture(Texture *tex, Rect2D rect);

private:
    RenderDevice *device = nullptr;
};
