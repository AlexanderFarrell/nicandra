#pragma once

#include "gl.hpp"
#include "gpu/mesh.hpp"

class OpenGLMesh : public GPUMesh {
private:
	GLsizei index_count = 0;
	GLuint vertex_array_object = 0;
	GLuint index_buffer_object = 0;
	std::vector<GLuint> vertex_buffer_objects;
public:
	std::expected<void, std::string> prepare(const Mesh &mesh) override;
	void draw() override;
	void destroy() override;
};
