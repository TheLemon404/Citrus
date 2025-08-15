#pragma once

#include <string>

#include "core.hpp"
#include <GLFW/glfw3.h>

namespace Citrus {
    class CITRUS_API Window {
        unsigned int width, height;
        std::string title;
        GLFWwindow* glfwWindow;

        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

    public:
        Window(unsigned int width, unsigned int height, std::string title) : width(width), height(height), title(title) {};

        void Open();
        bool ShouldClose();
        void SwapBuffersAndPoll();
        void Close();

        void OnResized(unsigned int width, unsigned int height);

        GLFWwindow* GetGLFWWindow() { return glfwWindow; }
        unsigned int GetWidth() { return width; }
        unsigned int GetHeight() { return height; }
    };
}
