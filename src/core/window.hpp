#pragma once

#include <string>

#include "core.hpp"
#include <GLFW/glfw3.h>

namespace Citrus {
    class CITRUS_API Window {
        unsigned int s_width, s_height;
        std::string m_title;
        GLFWwindow* s_glfwWindow;

        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

    public:
        Window(unsigned int width, unsigned int height, std::string title) : s_width(width), s_height(height), m_title(title) {};

        void Open();
        bool ShouldClose();
        void SwapBuffersAndPoll();
        void Close();

        void OnResized(unsigned int width, unsigned int height);

        GLFWwindow* GetGLFWWindow() { return s_glfwWindow; }
        unsigned int GetWidth() { return s_width; }
        unsigned int GetHeight() { return s_height; }
    };
}
