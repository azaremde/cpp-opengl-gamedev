#include "app/gui_layer.h"
#include "app/graphics_layer.h"

#include "environment/window.h"

#include <spdlog/spdlog.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

void GUILayer::init()
{    
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags = ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(window::window.get_window(), true);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();
}

void GUILayer::on_viewport_resize(const unsigned int width, const unsigned int height)
{
    graphics_layer->on_viewport_resize(width, height);
}

void GUILayer::update()
{
    
}

void GUILayer::render(gpu::wrap::GLFramebuffer* framebuffer)
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
		// ImGui::Image((void*)(intptr_t) framebuffer->get_texture_id(), ImVec2(render_area_width, render_area_height), uv0, uv1);
		ImGui::Image((void*)(intptr_t) graphics_layer->get_target()->get_texture_id(), ImVec2(render_area_width, render_area_height), uv0, uv1);
		
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

		ImGui::DragFloat3("Rotation", &graphics_layer->quad_rotation[0], 1, 0, 180, "%.06f", 1);
		ImGui::DragFloat3("Position", &graphics_layer->quad_position[0], 0.05f, -100, 100, "%.02f", 1);

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
}