#pragma once

#include "core.hpp"
#include "window.hpp"
#include "graphics/graphicsManager.hpp"

namespace Citrus {
    class CITRUS_API Application {
    public:
        Window m_window;
        GraphicsManager m_graphicsManager;

        Application();

        void Run();
    };
}
