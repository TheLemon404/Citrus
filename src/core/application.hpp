#pragma once

#include "core.hpp"
#include "window.hpp"
#include "graphics/graphicsManager.hpp"

namespace Citrus {
    class CITRUS_API Application {
        Window m_window;
        GraphicsManager m_graphicsManager;

    public:
        Application();

        void Run();
    };
}
