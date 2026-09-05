#pragma once

#include "gpu/gpu.hpp"
#include "opengl_mesh.hpp"
#include "opengl_shader.hpp"
#include "opengl_texture.hpp"
#include "opengl_uniform.hpp"
#include "util/data/slotmap.hpp"

class OpenGLGraphicsAPI: public GraphicsAPI {
	SlotMap<OpenGLMesh> _meshes;
	SlotMap<OpenGLShader> _shaders;
	SlotMap<OpenGLTexture> _textures;
	SlotMap<OpenGLUniform> _uniforms;
public:
	bool uses_opengl_window_context() override;
	std::unique_ptr<Renderer> create_renderer(uint16_t width, uint16_t height) override;
	~OpenGLGraphicsAPI() override;
	GenIndex create_gpu_mesh(const Mesh &mesh) override;
	GenIndex create_gpu_shader(const Shader &shader) override;
	GenIndex create_gpu_texture(const Texture &texture) override;
	GenIndex create_uniform_texture(const Uniform &uniform) override;
};