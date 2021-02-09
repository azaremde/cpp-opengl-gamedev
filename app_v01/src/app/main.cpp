#define ENGINE_DEBUG_MODE

#include "environment/window.h"

#include "layers/layer_manager.h"

#include "gui_layer.h"
#include "graphics_layer.h"

int main()
{
	window_init();

	layers::layer_manager.add_layer(new GUILayer());
	layers::layer_manager.add_layer(new GraphicsLayer());

	layers::layer_manager.init();

	while (!window_should_close())
	{
		window_poll_events();

		layers::layer_manager.update();

		window_swap_buffers();
		window_clear_state();
	}
	window_shutdown();

	return 0;
}