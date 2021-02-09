#pragma once

#include <string>

#include "gpu/wrappers/gl_framebuffer.h"

#include "layer_manager.h"

namespace layers {

class Layer
{
friend class LayerManager;

public:
    Layer(const std::string& name)
    {
        this->name = name;
    }

protected:
    virtual void init() {}
    virtual void update() {}
    virtual void render(gpu::wrap::GLFramebuffer* context) {}
    virtual void set_siblings() {}

    virtual gpu::wrap::GLFramebuffer* get_target() { return nullptr; }

private:
    std::string name;

};

}
