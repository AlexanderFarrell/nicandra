#include "opengl_mesh.hpp"
#include "gl.hpp"
#include "gpu/mesh.hpp"
#include <OpenGL/gltypes.h>
#include <cstddef>
#include <cstdint>
#include <vector>

std::expected<void, std::string> OpenGLMesh::prepare(const Mesh &mesh) {
	if (mesh.vertex_buffers.empty()) {
		return std::unexpected("Mesh must have at least one vertex buffer");
	}

	// Vertex array buffer, holds info on all vertex buffer objects.
	glGenVertexArrays(1, &this->vertex_array_object);
	glBindVertexArray(this->vertex_array_object);
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
		check_for_errors_gl();

		glVertexAttribPointer(i, vertex_buffer.elements_per_vertex, GL_FLOAT,
		                      GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(i);
		check_for_errors_gl();

		this->vertex_buffer_objects[i] = vbo;
	}

	// Index Buffer, we always use 32 bit indices
	GLsizeiptr indices_memory_size =
	    mesh.index_buffer.indices.size() * sizeof(uint32_t);
	glGenBuffers(1, &this->index_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_memory_size,
	             mesh.index_buffer.indices.data(), GL_STATIC_DRAW);
	this->index_count = mesh.index_buffer.indices.size();
	check_for_errors_gl();

	return {};
}

void OpenGLMesh::draw() {
	glBindVertexArray(this->vertex_array_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_object);
	glDrawElements(GL_TRIANGLES, this->index_count, GL_UNSIGNED_INT, (void *)0);
}

void OpenGLMesh::destroy() {
	glDeleteBuffers(1, &this->index_buffer_object);
	check_for_errors_gl();
	for (std::size_t i = 0; i < this->vertex_buffer_objects.size(); i++) {
		GLuint vbo = this->vertex_buffer_objects[i];
		glDeleteBuffers(1, &vbo);
		check_for_errors_gl();
	}

	glDeleteVertexArrays(1, &this->vertex_array_object);
	check_for_errors_gl();
}
