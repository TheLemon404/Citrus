#pragma once

#include <core/core.hpp>
#include "scene.hpp"

namespace Citrus {
    class CITRUS_API SceneManager {
        Scene currentScene;

    public:
        Scene& GetCurrentScene() { return currentScene; }
    };
}