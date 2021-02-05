#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "keyboard.h"

/*
* Here's what user might want to use.
*/
#define window_init()			window::init(&window::window)
#define window_should_close()	window::should_close(&window::window)
#define window_poll_events()	window::poll_events(&window::window)
#define window_clear()			window::clear(&window::window)
#define window_swap_buffers()	window::swap_buffers(&window::window)
#define window_clear_state()	window::clear_state(&window::window)
#define window_shutdown()		window::shutdown(&window::window)
#define window_close()			window::close(&window::window)

#define window_width()			window::window.width
#define window_height()			window::window.height
#define window_ratio()			(float) window::window.width / (float) window::window.height

namespace window {

enum class WindowMode
{
	Windowed,
	Borderless,
	Fullscreen
};

inline const WindowMode default_window_mode = WindowMode::Windowed;
inline const std::string default_window_title = "OpenGL application";

struct Window
{
	GLFWvidmode* p_glfw_video_mode;
	GLFWwindow* p_glfw_window;
	GLFWmonitor* p_glfw_primary_monitor;

	WindowMode window_mode = default_window_mode;

	unsigned int width;
	unsigned int height;

	#ifdef _DEBUG
	Window()
	{
		spdlog::info("Main window has been created.");
	}

	~Window()
	{
		spdlog::info("Main window has been destroyed.");
	}
	#endif

} inline window;

void on_resize(GLFWwindow* p_glfw_window, int width, int height);

void init(Window* p_window);
void init_glfw(Window* p_window);
void init_controllers(Window* p_window);
void set_callbacks(Window* p_window);
void init_glew();

void determine_resolution(Window* p_window);
void set_hints(Window* p_window);
void create_window(Window* p_window);

void poll_events(Window* p_window);
void clear(Window* p_window);
void swap_buffers(Window* p_window);
void clear_state(Window* p_window);
bool should_close(Window* p_window);
void shutdown(Window* p_window);

void close(Window* p_window);
	
}
