#pragma once

#include "gl_shader.h"

#define gl_shader_str_list(...)   std::vector<std::string> { ##__VA_ARGS__ }
#define gl_shader_inputs(...)     gl_shader_str_list(##__VA_ARGS__)
#define gl_shader_uniforms(...)   gl_shader_str_list(##__VA_ARGS__)

#define gl_create_shader(name, vs, fs, uniforms, inputs)\
class name : public gpu::wrap::GLShader\
{\
public:\
name() : gpu::wrap::GLShader(vs, fs, uniforms, inputs) {}\
}