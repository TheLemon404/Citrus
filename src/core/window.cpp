#include "window.hpp"

#include <GLFW/glfw3.h>

#include "log.hpp"

namespace Citrus {
    void Window::Open() {
        if (!glfwInit()) {
            CITRUS_CORE_ERROR("failed to initialize GLFW");
            return;
        }

        s_glfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
        if (!s_glfwWindow) {
            CITRUS_CORE_ERROR("failed to create GLFW window");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(s_glfwWindow);
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(s_glfwWindow);
    }

    void Window::SwapBuffersAndPoll() {
        glfwSwapBuffers(s_glfwWindow);
        glfwPollEvents();
    }

    void Window::Close() {
        glfwTerminate();
    }
}
