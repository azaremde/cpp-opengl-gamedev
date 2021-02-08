#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "keyboard.h"
#include "mouse.h"

/*
* Here's what user might want to use.
*/
#define window_init()			window::window.init()
#define window_should_close()	window::window.should_close()
#define window_poll_events()	window::window.poll_events()
#define window_clear()			window::window.clear()
#define window_swap_buffers()	window::window.swap_buffers()
#define window_clear_state()	window::window.clear_state()
#define window_shutdown()		window::window.shutdown()
#define window_close()			window::window.close()

#define window_width()			window::window.get_width()
#define window_height()			window::window.get_height()
#define window_ratio()			(float) window::window.get_width() / (float) window::window.get_height()

namespace window {

enum class WindowMode
{
	Windowed,
	Borderless,
	Fullscreen
};

inline const WindowMode default_window_mode = WindowMode::Windowed;
inline const std::string default_window_title = "OpenGL application";

/*
 * Even a singleton can look nice.. 
 */
class Window
{
private:
	GLFWvidmode* p_glfw_video_mode;
	GLFWwindow* p_glfw_window;
	GLFWmonitor* p_glfw_primary_monitor;

	WindowMode window_mode = default_window_mode;

	unsigned int width;
	unsigned int height;

	void init_glfw();
	void init_controllers();
	void set_callbacks();
	void init_glew();

	void determine_resolution();
	void set_hints();
	void create_window();

	static void on_resize(GLFWwindow* p_glfw_window, int width, int height);

	Window();
	
public:

	/* temp */ inline GLFWwindow* get_window()
	{
		return p_glfw_window;
	}

	static Window& get_instance();

	void init();
	bool should_close();
	void poll_events();
	void clear();
	void swap_buffers();
	void clear_state();
	void shutdown();
	void close();

	unsigned int get_width() const;
	unsigned int get_height() const;
};

inline Window window = Window::get_instance();
	
}
