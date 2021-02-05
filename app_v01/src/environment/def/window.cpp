#include "environment/window.h"

namespace window {

void determine_resolution(Window* p_window)
{
	p_window->p_glfw_primary_monitor = glfwGetPrimaryMonitor();
	p_window->p_glfw_video_mode = (GLFWvidmode*) glfwGetVideoMode(p_window->p_glfw_primary_monitor);
	p_window->width = p_window->p_glfw_video_mode->width;
	p_window->height = p_window->p_glfw_video_mode->height;
}

void set_hints(Window* p_window)
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	if (p_window->window_mode == WindowMode::Borderless)
	{
		glfwWindowHint(GLFW_RED_BITS, p_window->p_glfw_video_mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, p_window->p_glfw_video_mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, p_window->p_glfw_video_mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, p_window->p_glfw_video_mode->refreshRate);
	}
}

void init_controllers(Window* p_window)
{
	keyboard::init(p_window->p_glfw_window);
}

void on_resize(GLFWwindow* p_glfw_window, int width, int height)
{
	/*
	* We might want to return this.
	* glViewport(0, 0, width, height);
	*/
	window.width = width;
	window.height = height;
}

void set_callbacks(Window* p_window)
{
	//glfwSetCursorPosCallback(self.window, Mouse::onCursorMove);
	//glfwSetMouseButtonCallback(self.window, Mouse::onButtonPress);
	glfwSetWindowSizeCallback(p_window->p_glfw_window, on_resize);
	glfwSetKeyCallback(p_window->p_glfw_window, keyboard::on_key_press);
}

void create_window(Window* p_window)
{
	p_window->p_glfw_window = glfwCreateWindow(
		p_window->width,
		p_window->height,
		"",
		(p_window->window_mode == WindowMode::Borderless || p_window->window_mode == WindowMode::Fullscreen)
		? p_window->p_glfw_primary_monitor
		: NULL,
		NULL
	);

	glfwMakeContextCurrent(p_window->p_glfw_window);
	glfwSwapInterval(1);
	glfwMaximizeWindow(p_window->p_glfw_window);
	glfwShowWindow(p_window->p_glfw_window);
}

void init_glfw(Window* p_window)
{
	glfwInit();
	determine_resolution(p_window);
	set_hints(p_window);
	create_window(p_window);
}

void init_glew()
{
	glewInit();
	glewExperimental = GL_TRUE;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);

	// glClearColor(227.0f / 255.0f, 246.0f / 255.0f, 250.0f / 255.0f, 1);
}

void init(Window* p_window)
{
	init_glfw(p_window);
	init_controllers(p_window);
	set_callbacks(p_window);
	init_glew();
}

void poll_events(Window* p_window)
{
	glfwPollEvents();
}

void clear(Window* p_window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void swap_buffers(Window* p_window)
{
	glfwSwapBuffers(p_window->p_glfw_window);
}

void clear_state(Window* p_window)
{
	keyboard::clear_state();
}

bool should_close(Window* p_window)
{
	return glfwWindowShouldClose(p_window->p_glfw_window);
}

void shutdown(Window* p_window)
{
	glfwDestroyWindow(p_window->p_glfw_window);
	glfwTerminate();
}

void close(Window* p_window)
{
	glfwSetWindowShouldClose(p_window->p_glfw_window, true);
}

}