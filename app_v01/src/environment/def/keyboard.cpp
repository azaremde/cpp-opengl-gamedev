#include "environment/keyboard.h"

namespace keyboard {

void init(GLFWwindow* p_window)
{
    keyboard.p_window = p_window;
}

const bool key_pressed(const int& key)
{
    return keyboard.key_states[key] == ButtonState::Press;
}

const bool key_released(const int& key)
{
    return keyboard.key_states[key] == ButtonState::Release;
}

const bool key_down(const int& key)
{
    return glfwGetKey(keyboard.p_window, key);
}

void on_key_press(GLFWwindow* p_glfw_window, int key, int scancode, int action, int mods)
{
    switch (action)
    {
    case GLFW_RELEASE:
        keyboard.key_states[key] = ButtonState::Release;
        break;
    case GLFW_PRESS:
        keyboard.key_states[key] = ButtonState::Press;
        break;
    }
}

void clear_state()
{
    for (int i = 0; i < KEY_LAST; i++)
    {
        keyboard.key_states[i] = ButtonState::Idle;
    }
}

}