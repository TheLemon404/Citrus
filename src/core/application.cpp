#include "application.hpp"

#include "log.hpp"

namespace Citrus {
    Application::Application() : m_window(1024, 768, "Citrus"), m_graphicsManager(m_window) {
    }

    void Application::Run() {
        Log::Init();
        m_window.Open();
        m_graphicsManager.Init();

        while (!m_window.ShouldClose()) {
            m_graphicsManager.Draw();
            m_window.SwapBuffersAndPoll();
        }

        m_graphicsManager.CleanUp();
        m_window.Close();
    }
}
