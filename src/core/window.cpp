#include "window.hpp"

#include <GLFW/glfw3.h>

#include "application.hpp"
#include "log.hpp"

namespace Citrus {
    class Application;

    void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
        auto that = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        if (that != nullptr) {
            that->m_graphicsManager.OnFramebufferResized(width, height);
            that->m_window.OnResized(width, height);
        }
    }

    void Window::Open() {
        if (!glfwInit()) {
            CITRUS_CORE_ERROR("failed to initialize GLFW");
            return;
        }

        s_glfwWindow = glfwCreateWindow(s_width, s_height, m_title.c_str(), NULL, NULL);

        glfwSetFramebufferSizeCallback(s_glfwWindow, Window::FramebufferSizeCallback);
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

    void Window::OnResized(unsigned int width, unsigned int height) {
        s_width = width;
        s_height = height;
    }
}
