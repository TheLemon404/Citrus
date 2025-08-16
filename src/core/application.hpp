#pragma once

#include "core.hpp"
#include "window.hpp"
#include "graphics/graphicsManager.hpp"
#include "scene/sceneManager.hpp"

namespace Citrus {
    struct CITRUS_API ApplicationRenderResult {

    };

    class CITRUS_API Application {
    public:
        Window* window = nullptr;

        GraphicsManager graphicsManager;
        SceneManager sceneManager;

        Application(Window* window);

        void Init();
        void Update();
        ApplicationRenderResult Render();
        void Shutdown();
        bool ShouldClose();
    };
}
