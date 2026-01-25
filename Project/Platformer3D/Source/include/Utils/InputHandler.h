#pragma once

#include "MathPerso.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <iostream>
#include <unordered_map>
#include <functional>

class InputHandler
{
public:
    InputHandler() = default;
    ~InputHandler() = default;

    static void Destroy();

    static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseCursorCallback(GLFWwindow* window, double xpos, double ypos);
    static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    static bool IsKeyPressed(int key);
    static bool IsKeyDown(int key);
    static bool IsKeyReleased(int key);

    static bool IsMousePressed(int button);
    static bool IsMouseReleased(int button);

    static void SetMouseScrolling(double x, double y);
    static Vector2D IsMouseScrolling();

    static void SetMousePos(double x, double y);
    static Vector2D GetMousePos();
    static void ProcessPressedKeys();

    static void CallKeyFunc(int key);
    static bool isKeyInMap(int key);
    static void BindKeyToFunc(int key, std::function<void(int)> func);
    static int GetMappedKey(std::function<void(int)> func);

    static std::unordered_map<int, std::function<void(int)>> keyMapping;

private:
    static std::vector<int> m_CurrentKeyStatus;
    static std::vector<int> m_pressedKey;
    static std::vector<int> m_MouseButtonKeyStatus;

    static Vector2D mousePos;
    static Vector2D wheelPos;
};