#pragma once

#include "core.hpp"
#include "window.hpp"
#include "graphics/graphicsManager.hpp"
#include "scene/sceneManager.hpp"

namespace Citrus {
    class CITRUS_API Application {
    public:
        Window window;
        GraphicsManager graphicsManager;
        SceneManager sceneManager;

        Application();

        void Run();
    };
}
