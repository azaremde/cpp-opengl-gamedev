#define ENGINE_DEBUG_MODE

#include "environment/entry_point.h"
#include "environment/keyboard.h"
#include "environment/window.h"

#include "render/shaders/static_shader.h"
#include "gpu/wrappers/gl_vao.h"

#include "assets/asset.h"

#include "math/math.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <spdlog/spdlog.h>

#include <GL/glew.h>

#include <stb_image/stb_image.h>

class Sandbox : public App
{
private:
	render::shaders::StaticShader shader;
	gpu::wrap::GLvao vao;

	glm::mat4x4 proj = glm::mat4x4(1);
	glm::mat4x4 model = glm::mat4x4(1);

public:
	void init() override
	{
		assets::Text text;
		assets::load(&text, "assets/foo.txt");

		spdlog::info(text.content);

		vao.bind();
		vao.create_attribute(0, std::vector<float> { 
			-0.5,  0.5, 0,
			-0.5, -0.5, 0,
			 0.5, -0.5, 0,
			 0.5,  0.5, 0
		}, 3);
		vao.create_index_buffer(std::vector<int> { 0, 1, 2, 2, 3, 0 });
		vao.unbind();

		proj = glm::perspective(glm::radians(70.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
	}

	float alpha = 0;

	void __render__() override
	{
		model = glm::rotate(model, glm::radians(0.2f), glm::vec3(0, 1, 0));

		shader.bind();
		shader.set_mat4x4("u_model", model);
		shader.set_mat4x4("u_proj", proj);
		vao.bind();
		glDrawElements(GL_TRIANGLES, vao.get_vertex_count(), GL_UNSIGNED_INT, nullptr);
		vao.unbind();
		shader.unbind();
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