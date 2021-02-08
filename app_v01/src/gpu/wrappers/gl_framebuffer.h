#pragma once

#include <GL/glew.h>

namespace gpu {
namespace wrap {

class GLFramebuffer
{
private:
    GLuint framebuffer_id;
    GLuint texture_id;
    GLuint depthbuffer_id;

	void init_framebuffer();
	void init_texture(const unsigned int& width, const unsigned int& height);
	void init_depth_buffer(const unsigned int& width, const unsigned int& height);
	void configure_framebuffer();

public:
    GLFramebuffer(const unsigned int& width, const unsigned int& height);

    inline void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
    }

    inline void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void resize(const unsigned int& width, const unsigned int& height)
    {
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

        bind();
		glViewport(0, 0, width, height);
        unbind();
    }

    inline static void unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    GLuint get_framebuffer_id() const;
    GLuint get_texture_id() const;
    GLuint get_depthbuffer_id() const;
};

}
}