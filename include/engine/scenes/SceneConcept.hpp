#pragma once
#include "engine/scenes/Scene.hpp"

template <typename T>
concept SceneConcept = std::derived_from<T, Scene>;