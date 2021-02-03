#include <spdlog/spdlog.h>

#include "environment/entry_point.h"
#include "environment/keyboard.h"
#include "environment/window.h"

class Sandbox : public App
{
public:
	void init() override
	{

	}

	void update(const float& deltaTime) override
	{
		if (keyboard_key_pressed(KEY_ESCAPE))
		{
			window_close();
		}

		if (keyboard_key_pressed(KEY_SPACE))
		{
			spdlog::info("Width: {0}", window_width());
			spdlog::info("Height: {0}", window_height());
			spdlog::info("Ratio: {0}", window_ratio());
		}
	}
};

engine_entry(Sandbox);