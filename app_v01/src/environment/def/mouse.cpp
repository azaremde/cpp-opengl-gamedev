#include "environment/mouse.h"

namespace mouse {

void init(GLFWwindow* p_window)
{
    mouse.p_window = p_window;
}

const bool button_pressed(const int& button)
{
    return mouse.button_states[button] == ButtonState::Press;
}

const bool button_released(const int& button)
{
    return mouse.button_states[button] == ButtonState::Release;
}

const bool button_down(const int& button)
{
    return glfwGetMouseButton(mouse.p_window, button);
}

void on_button_press(GLFWwindow* p_glfw_window, int button, int action, int mods)
{
    switch (action)
    {
    case GLFW_RELEASE:
        mouse.button_states[button] = ButtonState::Release;
        break;
    case GLFW_PRESS:
        mouse.button_states[button] = ButtonState::Press;
        break;
    }
}

void clear_state()
{
    for (int i = 0; i < MOUSE_BUTTON_LAST; i++)
    {
        mouse.button_states[i] = ButtonState::Idle;
    }
}

}