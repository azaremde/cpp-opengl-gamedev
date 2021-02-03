#pragma once

#include "environment/window.h"
#include "environment/app.h"

#define engine_entry(App)\
int main()\
{\
	window_init();\
	App* app = new App();\
	app->init();\
	while (!window_should_close())\
	{\
		window_poll_events();\
		app->update(0);\
		window_clear();\
		window_swap_buffers();\
		window_clear_state();\
	}\
	window_shutdown();\
	return 0;\
}