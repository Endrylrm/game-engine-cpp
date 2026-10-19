#pragma once
#include <engine/core/handle/TypedHandle.hpp>

struct BufferTag;
using BufferHandle = TypedHandle<BufferTag>;

struct MeshTag;
using MeshHandle = TypedHandle<MeshTag>;

struct ShaderTag;
using ShaderHandle = TypedHandle<ShaderTag>;

struct TextureTag;
using TextureHandle = TypedHandle<TextureTag>;

struct PipelineTag;
using PipelineHandle = TypedHandle<PipelineTag>;
