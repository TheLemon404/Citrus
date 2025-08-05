#include "application.hpp"

namespace Citrus {
    Application::Application() : m_window(1024, 768, "Citrus") {
        m_graphicsManager = GraphicsManager();
    }

    void Application::Run() {
        m_window.Open();
        m_graphicsManager.Init();

        while (!m_window.ShouldClose()) {
            m_window.SwapBuffersAndPoll();
        }

        m_window.Close();
    }
}