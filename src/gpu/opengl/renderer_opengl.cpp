#include "renderer_opengl.hpp"
#include "gl.hpp"
#include <GLFW/glfw3.h>

static bool glad_loaded = false;

void OpenGLRenderer::setup() {
	if (!glad_loaded) {
		gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		glad_loaded = true;
	}
}

void OpenGLRenderer::breakdown() {
}

void OpenGLRenderer::render(GLFWwindow* window) {
	// Beginning Renderer
	glfwMakeContextCurrent(window);
	glViewport(0, 0, this->width, this->height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(this->clear_color.r, this->clear_color.g, this->clear_color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);

	// Draw drawables

	// End draw
	glFlush();
}
OpenGLRenderer::~OpenGLRenderer() {}
