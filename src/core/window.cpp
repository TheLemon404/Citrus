#include "window.hpp"

#include <GLFW/glfw3.h>

#include "application.hpp"
#include "log.hpp"

namespace Citrus {
    class Application;

    void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
        auto that = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        if (that != nullptr) {
            that->graphicsManager.OnFramebufferResized(width, height);
            that->window->OnResized(width, height);
        }
    }

    void Window::Open() {
        if (!glfwInit()) {
            CITRUS_CORE_ERROR("failed to initialize GLFW");
            return;
        }

        glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

        glfwSetFramebufferSizeCallback(glfwWindow, Window::FramebufferSizeCallback);
        if (!glfwWindow) {
            CITRUS_CORE_ERROR("failed to create GLFW window");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(glfwWindow);
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(glfwWindow);
    }

    void Window::SwapBuffersAndPoll() {
        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    void Window::Close() {
        glfwTerminate();
    }

    void Window::OnResized(unsigned int width, unsigned int height) {
        width = width;
        height = height;
    }
}
