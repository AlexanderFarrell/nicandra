#pragma once
#include "renderer.hpp"
#include "../util/data/slotmap.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "uniform.hpp"
#include "drawable.hpp"

/**
* An abstraction over a graphics API such as OpenGL, Vulkan, DirectX or Metal.
 */
class GraphicsAPI {
public:
	virtual ~GraphicsAPI();

	/**
	* Returns true if we should let GLFW make an OpenGL context, false
	* otherwise. Basically it's true only for OpenGL.
	 */
	virtual bool uses_opengl_window_context() = 0;

	virtual std::unique_ptr<Renderer> create_renderer(uint16_t width, uint16_t height) = 0;

	virtual GenIndex create_gpu_mesh(const Mesh& mesh) = 0;
	virtual GenIndex create_gpu_shader(const Shader& shader) = 0;
	virtual GenIndex create_gpu_texture(const Texture& texture) = 0;
	virtual GenIndex create_uniform_texture(const Uniform& uniform) = 0;
};

/**
* An abstraction over a GPU general compute API, such as OpenCL, CUDA, Vulkan,
* DirectX12, Metal, etc.
 */
class ComputeAPI {

};
