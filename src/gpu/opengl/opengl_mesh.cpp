#include "opengl_mesh.hpp"
#include "gl.hpp"
#include <vector>

std::expected<void, std::string> OpenGLMesh::prepare(const Mesh &mesh) {
	if (mesh.vertex_buffers.empty()) {
		return std::unexpected("Mesh must have at least one vertex buffer");
	}

	// Vertex array buffer, holds info on all vertex buffer objects.
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	check_for_errors_gl();

	this->vertex_buffer_objects.resize(mesh.vertex_buffers.size());

	for (std::size_t i = 0; i < mesh.vertex_buffers.size(); ++i) {
		const VertexBuffer &vertex_buffer = mesh.vertex_buffers[i];
		GLuint vbo;
		GLsizeiptr size = vertex_buffer.data.size() * sizeof(float);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertex_buffer.data.data(),
		             GL_STATIC_DRAW);
	}
}

std::expected<void, std::string> OpenGLMesh::refresh(const Mesh &mesh) {}

void OpenGLMesh::draw() {}

void OpenGLMesh::destroy() {}
