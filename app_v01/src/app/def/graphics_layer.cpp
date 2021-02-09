#include "app/graphics_layer.h"
#include "app/gui_layer.h"

#include "environment/keyboard.h"

void GraphicsLayer::init()
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

    framebuffer = new gpu::wrap::GLFramebuffer(2048, 2048);
}

void GraphicsLayer::on_viewport_resize(const unsigned int& width, const unsigned int& height)
{
	proj = glm::perspective(
		glm::radians(70.0f),
		static_cast<float>(width) / static_cast<float>(height),
		0.1f,
		1000.0f
	);
	
	framebuffer->resize(width, height);
}

void GraphicsLayer::update()
{
	// Scene "physics"
	model = glm::identity<glm::mat4x4>();
	model = glm::translate(model, quad_position);
	model = glm::rotate(model, glm::radians(quad_rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(quad_rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(quad_rotation.z), glm::vec3(0, 0, 1));
}

void GraphicsLayer::render(gpu::wrap::GLFramebuffer* context)
{
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    context->bind();
    context->clear();

	// Render to texture
	shader.bind();
	shader.set_mat4x4("u_model", model);
	shader.set_mat4x4("u_proj", proj);
	vao.bind();
	glDrawElements(GL_TRIANGLES, vao.get_vertex_count(), GL_UNSIGNED_INT, nullptr);
	vao.unbind();
	shader.unbind();

    context->unbind();
	// gpu::wrap::GLFramebuffer::unbind();
}

gpu::wrap::GLFramebuffer* GraphicsLayer::get_target()
{
    return framebuffer;
}