#include "opengl.hpp"
#include "renderer_opengl.hpp"

bool OpenGLGraphicsAPI::uses_opengl_window_context() {
	return true;
}

std::unique_ptr<Renderer> OpenGLGraphicsAPI::create_renderer(uint16_t width, uint16_t height) {
	return std::make_unique<OpenGLRenderer>(width, height);
}
