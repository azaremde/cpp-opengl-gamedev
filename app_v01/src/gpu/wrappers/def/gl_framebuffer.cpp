#include "gpu/wrappers/gl_framebuffer.h"

namespace gpu {
namespace wrap {

GLFramebuffer::GLFramebuffer(const unsigned int& width, const unsigned int& height)
{
    init_framebuffer();
    init_texture(width, height);
    init_depth_buffer(width, height);
    configure_framebuffer();
}

void GLFramebuffer::init_framebuffer()
{
    glGenFramebuffers(1, &framebuffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
}

void GLFramebuffer::init_texture(const unsigned int& width, const unsigned int& height)
{
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void GLFramebuffer::init_depth_buffer(const unsigned int& width, const unsigned int& height)
{
    // The depth buffer
    glGenRenderbuffers(1, &depthbuffer_id);
    glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer_id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer_id);
}

void GLFramebuffer::configure_framebuffer()
{
    // Set "renderedTexture" as our color attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
}

GLuint GLFramebuffer::get_framebuffer_id() const
{
    return framebuffer_id;
}

GLuint GLFramebuffer::get_texture_id() const
{
    return texture_id;
}

GLuint GLFramebuffer::get_depthbuffer_id() const
{
    return depthbuffer_id;
}

}
}
