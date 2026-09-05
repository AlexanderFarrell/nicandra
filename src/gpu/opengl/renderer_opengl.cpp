#include "renderer_opengl.hpp"
#include "gl.hpp"
#include <GLFW/glfw3.h>

#if OPENGL_USES_GLAD
static bool glad_loaded = false;
#endif

void OpenGLRenderer::setup() {
#if OPENGL_USES_GLAD
	if (!glad_loaded) {
		gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		glad_loaded = true;
	}
#endif
}

void OpenGLRenderer::breakdown() {}

void OpenGLRenderer::render(GLFWwindow *window) {
	// Beginning Renderer
	glfwMakeContextCurrent(window);
	glViewport(0, 0, this->width, this->height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(this->clear_color.r, this->clear_color.g, this->clear_color.b,
	             1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);

	// Draw drawables

	// End draw
	glFlush();
}
OpenGLRenderer::~OpenGLRenderer() {}
