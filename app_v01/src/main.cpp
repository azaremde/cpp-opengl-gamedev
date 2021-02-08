#define ENGINE_DEBUG_MODE

#include "environment/entry_point.h"
#include "environment/keyboard.h"
#include "environment/window.h"
#include "environment/mouse.h"

#include "render/shaders/static_shader.h"
#include "gpu/wrappers/gl_framebuffer.h"
#include "gpu/wrappers/gl_vao.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <spdlog/spdlog.h>

#include <GL/glew.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

/*
 * TODO:
 * 		Disassemle all of this and move to main(),
 * 		in order to be able to maintain it properly.
 * 
 * 		Create "layers". In the engine they divide imgui and scene,
 * 		in a game they would divide GUI and scene.
 * 		Also, what about a physics-layer?
 * 		There must be a way for the layers to interact with each other.
 */

class Sandbox : public App
{
private:
	render::shaders::StaticShader shader;
	gpu::wrap::GLvao vao;

	glm::mat4x4 /* temp */ proj = glm::mat4x4(1);
	glm::mat4x4 /* temp */ model = glm::mat4x4(1);

	glm::vec3 /* temp */ quad_position = glm::vec3(0.0f, 0.0f, -5.0f);
	glm::vec3 /* temp */ quad_rotation = glm::vec3(0.0f);
	
	GLuint /* temp */ render_area_width = 0;
	GLuint /* temp */ render_area_height = 0;	
	GLuint /* temp */ last_render_area_width = 0;
	GLuint /* temp */ last_render_area_height = 0;

	gpu::wrap::GLFramebuffer* /* temp */ framebuffer;

	void init_imgui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags = ImGuiConfigFlags_DockingEnable;

		ImGui_ImplGlfw_InitForOpenGL(window::window.get_window(), true);
		ImGui_ImplOpenGL3_Init();

		ImGui::StyleColorsDark();
	}

	void on_viewport_resize(const unsigned int& new_width, const unsigned int& new_height)
	{
		proj = glm::perspective(
			glm::radians(70.0f),
			static_cast<float>(new_width) / static_cast<float>(new_height),
			0.1f,
			1000.0f
		);
		
		framebuffer->resize(new_width, new_height);
	}

	void render_imgui()
	{
		// Callback on viewport resize
		if (mouse_button_released(MOUSE_BUTTON_1) && (last_render_area_width != render_area_width || last_render_area_height != render_area_height))
		{
			on_viewport_resize(render_area_width, render_area_height);

			last_render_area_width = render_area_width;
			last_render_area_height = render_area_height;
		}

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		static ImGuiID dockspace_id = 0;
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(window_width(), window_height()));
		if (ImGui::Begin("Engine 1.0"))
		{
			dockspace_id = ImGui::GetID("HUB_DockSpace");
			ImGui::DockSpace(dockspace_id , ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
		}
		ImGui::End();

		ImGui::SetNextWindowDockID(dockspace_id , ImGuiCond_FirstUseEver);
		ImGui::Begin("Scene");
		
			// We need to flip uv.v to render it properly, since we created texture with opengl.
			ImVec2 uv0 = ImVec2(0, 1);
			ImVec2 uv1 = ImVec2(1, 0);
			ImGui::Image((void*)(intptr_t) framebuffer->get_texture_id(), ImVec2(render_area_width, render_area_height), uv0, uv1);
			
			ImVec2 vMin = ImGui::GetWindowContentRegionMin();
			ImVec2 vMax = ImGui::GetWindowContentRegionMax();

			vMin.x += ImGui::GetWindowPos().x;
			vMin.y += ImGui::GetWindowPos().y;
			vMax.x += ImGui::GetWindowPos().x;
			vMax.y += ImGui::GetWindowPos().y;

			render_area_width = vMax.x - vMin.x;
			render_area_height = vMax.y - vMin.y;

		ImGui::End();

		ImGui::SetNextWindowDockID(dockspace_id , ImGuiCond_FirstUseEver);
		ImGui::Begin("Transform");

			ImGui::DragFloat3("Rotation", &quad_rotation[0], 1, 0, 180, "%.06f", 1);
			ImGui::DragFloat3("Position", &quad_position[0], 0.05f, -100, 100, "%.02f", 1);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGui::UpdatePlatformWindows();
	}

public:
	void init() override
	{
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

		init_imgui();

		framebuffer = new gpu::wrap::GLFramebuffer(2048, 2048);
	}

	void __render__() override
	{
		// Scene "physics"
		model = glm::identity<glm::mat4x4>();
		model = glm::translate(model, quad_position);
		model = glm::rotate(model, glm::radians(quad_rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(quad_rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(quad_rotation.z), glm::vec3(0, 0, 1));
		
		framebuffer->bind();
		framebuffer->clear();

		// Render to texture
		shader.bind();
		shader.set_mat4x4("u_model", model);
		shader.set_mat4x4("u_proj", proj);
		vao.bind();
		glDrawElements(GL_TRIANGLES, vao.get_vertex_count(), GL_UNSIGNED_INT, nullptr);
		vao.unbind();
		shader.unbind();

		gpu::wrap::GLFramebuffer::unbind();

		// Render gui
		render_imgui();
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