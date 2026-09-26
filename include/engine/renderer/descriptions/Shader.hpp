#pragma once
#include <span>
#include <string>
#include <vector>

enum class ShaderStage
{
    Vertex,
    Fragment,
    Geometry,
    Compute,
    TessellationControl,
    TessellationEvaluation
};

struct ShaderSource
{
    ShaderStage stage;
    std::string source;
};

struct ShaderDescription
{
    std::vector<ShaderSource> sources;
};

inline ShaderDescription makeShaderDescription(std::span<const ShaderSource> sources)
{
    ShaderDescription desc;
    desc.sources.assign(sources.begin(), sources.end());
    return desc;
}
