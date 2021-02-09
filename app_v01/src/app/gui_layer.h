#pragma once

#include "layers/layer_manager.h"
#include "layers/layer.h"

#include "gpu/wrappers/gl_framebuffer.h"

#include <string>

class GraphicsLayer;

class GUILayer : public layers::Layer
{
friend class GraphicsLayer;

public:    
    GUILayer() : layers::Layer("GUILayer") {}

private:
    GraphicsLayer* graphics_layer;

    unsigned int render_area_width = 0;
    unsigned int render_area_height = 0;	
    unsigned int last_render_area_width = 0;
    unsigned int last_render_area_height = 0;

    virtual void init();
    virtual void update();
    virtual void render(gpu::wrap::GLFramebuffer* framebuffer);

    inline virtual void set_siblings() override
    {
        graphics_layer = (GraphicsLayer*) layers::layer_manager.find_layer("GraphicsLayer");
    }

    void on_viewport_resize(const unsigned int width, const unsigned int height);
};
