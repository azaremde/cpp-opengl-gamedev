#include "environment/window.h"

#include <spdlog/spdlog.h>

namespace window {

Window::Window()
{
#	if defined _DEBUG || defined ENGINE_DEBUG_MODE
		spdlog::info("Window instance has been created.");
#	endif
}

void Window::determine_resolution()
{
	p_glfw_primary_monitor = glfwGetPrimaryMonitor();
	p_glfw_video_mode = (GLFWvidmode*) glfwGetVideoMode(p_glfw_primary_monitor);
	width = p_glfw_video_mode->width;
	height = p_glfw_video_mode->height;
}

void Window::set_hints()
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	if (window_mode == WindowMode::Borderless)
	{
		glfwWindowHint(GLFW_RED_BITS, p_glfw_video_mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, p_glfw_video_mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, p_glfw_video_mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, p_glfw_video_mode->refreshRate);
	}
}

void Window::init_controllers()
{
	keyboard::init(p_glfw_window);
}

void Window::set_callbacks()
{
	//glfwSetCursorPosCallback(self.window, Mouse::onCursorMove);
	//glfwSetMouseButtonCallback(self.window, Mouse::onButtonPress);
	glfwSetWindowSizeCallback(p_glfw_window, on_resize);
	glfwSetKeyCallback(p_glfw_window, keyboard::on_key_press);
}

void Window::create_window()
{
	p_glfw_window = glfwCreateWindow(
		width,
		height,
		default_window_title.c_str(),
		(window_mode == WindowMode::Borderless || window_mode == WindowMode::Fullscreen)
		? p_glfw_primary_monitor
		: NULL,
		NULL
	);

	glfwMakeContextCurrent(p_glfw_window);
	glfwSwapInterval(1);
	glfwMaximizeWindow(p_glfw_window);
	glfwShowWindow(p_glfw_window);
}

void Window::init_glfw()
{
	glfwInit();
	determine_resolution();
	set_hints();
	create_window();
}

void Window::init_glew()
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

void Window::init()
{
	init_glfw();
	init_controllers();
	set_callbacks();
	init_glew();
}

void Window::poll_events()
{
	glfwPollEvents();
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap_buffers()
{
	glfwSwapBuffers(p_glfw_window);
}

void Window::clear_state()
{
	keyboard::clear_state();
}

bool Window::should_close()
{
	return glfwWindowShouldClose(p_glfw_window);
}

void Window::shutdown()
{
	glfwDestroyWindow(p_glfw_window);
	glfwTerminate();
}

void Window::close()
{
	glfwSetWindowShouldClose(p_glfw_window, true);
}

void Window::on_resize(GLFWwindow* p_glfw_window, int width, int height)
{
	/*
	* We might want to return this.
	* glViewport(0, 0, width, height);
	*/
	window.width = width;
	window.height = height;
}

Window& Window::get_instance()
{
	static Window instance;
	return instance;
}

unsigned int Window::get_width() const
{
	return width;
}

unsigned int Window::get_height() const
{
	return height;
}

}