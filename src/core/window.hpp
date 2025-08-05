#pragma once

#include <string>

#include "core.hpp"
#include <GLFW/glfw3.h>

namespace Citrus {
    class CITRUS_API Window {
        unsigned int m_width, m_height;
        std::string m_title;
        GLFWwindow* m_glfwWindow;

    public:
        Window(unsigned int width, unsigned int height, std::string title) : m_width(width), m_height(height), m_title(title) {};

        void Open();
        bool ShouldClose();
        void SwapBuffersAndPoll();
        void Close();
    };
}
