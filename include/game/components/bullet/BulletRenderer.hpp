#pragma once
#include <string>
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/Transform2D.hpp"
#include "engine/core/graphics/Renderer.hpp"
#include "engine/assets/AssetHandle.hpp"
#include "engine/core/graphics/Texture.hpp"

class BulletRenderer : public Component
{
public:
    void onStart() override;
    void onRender(Renderer &renderer) override;

private:
    Transform2D *transform = nullptr;
    AssetHandle<Texture> texture;
};
