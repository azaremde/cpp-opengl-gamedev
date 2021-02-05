#pragma once

#include "gpu/wrappers/gl_shader_macros.h"

namespace render {
namespace shaders {

gl_create_shader(
    StaticShader,
    "assets/shaders/static/static_shader_vert.glsl",
    "assets/shaders/static/static_shader_frag.glsl",
    gl_shader_uniforms("u_proj", "u_model"),
    gl_shader_inputs("in_position")
);

}
}