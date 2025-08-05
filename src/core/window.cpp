#include "window.hpp"

#include <GLFW/glfw3.h>

#include "log.hpp"

namespace Citrus {
    void Window::Open() {
        if (!glfwInit()) {
            CITRUS_CORE_ERROR("failed to initialize GLFW");
            return;
        }

        m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
        if (!m_glfwWindow) {
            CITRUS_CORE_ERROR("failed to create GLFW window");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_glfwWindow);
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(m_glfwWindow);
    }

    void Window::SwapBuffersAndPoll() {
        glfwSwapBuffers(m_glfwWindow);
        glfwPollEvents();
    }

    void Window::Close() {
        glfwTerminate();
    }
}
