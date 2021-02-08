#pragma once

#include <GLFW/glfw3.h>

#include <vector>

#include "buttons.h"

#define mouse_button_pressed(key)	mouse::button_pressed(key)
#define mouse_button_released(key)	mouse::button_released(key)
#define mouse_button_down(key)		mouse::button_down(key)

namespace mouse {

enum class ButtonState
{
	Idle = 0,
	Release,
	Press,
};

struct Mouse
{
	GLFWwindow* p_window;

	ButtonState button_states[MOUSE_BUTTON_LAST];

} inline mouse;

void init(GLFWwindow* p_window);

const bool button_pressed(const int& key);
const bool button_released(const int& key);
const bool button_down(const int& key);

void on_button_press(GLFWwindow* p_glfw_window, int key, int action, int mods);

void clear_state();

}