#pragma once
#include <memory>
#include <string>

#include "engine/core/math/Color.hpp"
#include "engine/core/math/Rect2D.hpp"
#include "engine/renderer/descriptions/Mesh.hpp"
#include "engine/renderer/descriptions/Shader.hpp"
#include "engine/renderer/descriptions/Texture.hpp"
#include "engine/renderer/resources/Mesh.hpp"
#include "engine/renderer/resources/Pipeline.hpp"
#include "engine/renderer/resources/Shader.hpp"
#include "engine/renderer/resources/Texture.hpp"

class RenderDevice
{
public:
    virtual ~RenderDevice() = default;

    virtual bool init() = 0;
    virtual void clear(Color color) = 0;
    virtual void present() = 0;
    virtual void setViewport(Rect2D rect) = 0;

    virtual std::unique_ptr<Texture> createTexture(const std::string &path) = 0;

    virtual void drawTexture(Texture *texture, Rect2D rect) = 0;
    virtual void drawRect(Rect2D rect, Color color) = 0;
};
