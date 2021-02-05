#pragma once

#include <GLFW/glfw3.h>

#include <vector>

#include "keys.h"

#define keyboard_key_pressed(key)	keyboard::key_pressed(key)
#define keyboard_key_released(key)	keyboard::key_released(key)
#define keyboard_key_down(key)		keyboard::key_down(key)

namespace keyboard {

enum class ButtonState
{
	Idle = 0,
	Release,
	Press,
};

struct Keyboard
{
	GLFWwindow* p_window;

	ButtonState key_states[KEY_LAST];

} inline static keyboard;

void init(GLFWwindow* p_window);

const bool key_pressed(const int& key);
const bool key_released(const int& key);
const bool key_down(const int& key);

void on_key_press(GLFWwindow* p_glfw_window, int key, int scancode, int action, int mods);

void clear_state();

}