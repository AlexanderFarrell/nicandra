#pragma once

#include "gpu/mesh.hpp"
#include "gl.hpp"

class OpenGLMesh: public GPUMesh {
private:
	std::vector<GLuint> vertex_buffer_objects;
public:
	std::expected<void, std::string> prepare(const Mesh &mesh) override;
	std::expected<void, std::string> refresh(const Mesh &mesh) override;
	void draw() override;
	void destroy() override;
};