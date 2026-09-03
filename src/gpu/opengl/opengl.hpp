#pragma once

#include "gpu/gpu.hpp"

class OpenGLGraphicsAPI: public GraphicsAPI {
	bool uses_opengl_window_context() override;
public:
	std::unique_ptr<Renderer> create_renderer(uint16_t width, uint16_t height) override;
	~OpenGLGraphicsAPI() override;
	GenIndex create_gpu_mesh(const Mesh &mesh) override;
	GenIndex create_gpu_shader(const Shader &shader) override;
	GenIndex create_gpu_texture(const Texture &texture) override;
	GenIndex create_uniform_texture(const Uniform &uniform) override;
};