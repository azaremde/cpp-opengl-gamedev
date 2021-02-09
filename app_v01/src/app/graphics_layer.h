#pragma once

#include "layers/layer.h"

#include "gpu/wrappers/gl_vao.h"

#include "render/shaders/static_shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

class GUILayer;

class GraphicsLayer : public layers::Layer
{
friend class GUILayer;

public:
    GraphicsLayer() : layers::Layer("GraphicsLayer") {}

private:
    GUILayer* gui_layer;

    render::shaders::StaticShader shader;
    gpu::wrap::GLvao vao;

    glm::mat4x4 proj = glm::mat4x4(1);
    glm::mat4x4 model = glm::mat4x4(1);

    gpu::wrap::GLFramebuffer* framebuffer;

    glm::vec3 quad_position = glm::vec3(0.0f, 0.0f, -5.0f);
    glm::vec3 quad_rotation = glm::vec3(0.0f);

    virtual void init();
    virtual void update();
    virtual void render(gpu::wrap::GLFramebuffer* context);
    virtual gpu::wrap::GLFramebuffer* get_target();

    inline virtual void set_siblings() override
    {
        gui_layer = (GUILayer*) layers::layer_manager.find_layer("GUILayer");
    }

    void on_viewport_resize(const unsigned int& width, const unsigned int& height);
};
