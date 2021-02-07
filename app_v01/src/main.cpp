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

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplGlfw_InitForOpenGL(window::window.get_window(), true);
		ImGui_ImplOpenGL3_Init();

		// Setup style
		ImGui::StyleColorsDark();

		glDisable(GL_CULL_FACE);
	}

	float rot_x = 0;
	float rot_y = 0;
	float rot_z = 0;

	glm::vec3 quad_position;
	glm::vec3 quad_rotation;

	void __render__() override
	{
		model = glm::identity<glm::mat4x4>();
		model = glm::translate(model, quad_position);
		model = glm::rotate(model, glm::radians(quad_rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(quad_rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(quad_rotation.z), glm::vec3(0, 0, 1));

		shader.bind();
		shader.set_mat4x4("u_model", model);
		shader.set_mat4x4("u_proj", proj);
		vao.bind();
		glDrawElements(GL_TRIANGLES, vao.get_vertex_count(), GL_UNSIGNED_INT, nullptr);
		vao.unbind();
		shader.unbind();



        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		ImGui::Begin("Transform");
		ImGui::Button("Reset");
		ImGui::SliderFloat("rot_x", &quad_rotation.x, 0.0f, 180.0f);
		ImGui::SliderFloat("rot_y", &quad_rotation.y, 0.0f, 180.0f);
		ImGui::SliderFloat("rot_z", &quad_rotation.z, 0.0f, 180.0f);
		ImGui::SliderFloat("pos_x", &quad_position.x, -20.0f, 20.0f);
		ImGui::SliderFloat("pos_y", &quad_position.y, -20.0f, 20.0f);
		ImGui::SliderFloat("pos_z", &quad_position.z, -20.0f, 20.0f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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