#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "App.h"
#include "Camera.h"

class WindowHandler
{
public:
    WindowHandler() = default;
    ~WindowHandler() = default;

    static void WindowResizeCallback(GLFWwindow* window, int width, int height);
    static void BufferResizeCallback(GLFWwindow* window, int width, int height);
};