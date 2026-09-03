#include "opengl.hpp"
#include "renderer_opengl.hpp"

bool OpenGLGraphicsAPI::uses_opengl_window_context() {
	return true;
}

std::unique_ptr<Renderer> OpenGLGraphicsAPI::create_renderer(uint16_t width, uint16_t height) {
	return std::make_unique<OpenGLRenderer>(width, height);
}
OpenGLGraphicsAPI::~OpenGLGraphicsAPI() {}
GenIndex OpenGLGraphicsAPI::create_gpu_mesh(const Mesh &mesh) {
	return GenIndex();
}
GenIndex OpenGLGraphicsAPI::create_gpu_shader(const Shader &shader) {
	return GenIndex();
}
GenIndex OpenGLGraphicsAPI::create_gpu_texture(const Texture &texture) {
	return GenIndex();
}
GenIndex OpenGLGraphicsAPI::create_uniform_texture(const Uniform &uniform) {
	return GenIndex();
}
