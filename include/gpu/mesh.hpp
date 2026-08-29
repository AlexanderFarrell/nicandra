#pragma once

#include <vector>

class VertexBuffer {
	std::vector<float> data;
	int elements_per_vertex;

	VertexBuffer() = default;
	explicit VertexBuffer(int elements_per_vertex): elements_per_vertex(elements_per_vertex) {}
	VertexBuffer(int elemenets_per_vertex, std::vector<float> data): elements_per_vertex(elemenets_per_vertex), data(std::move(data)) {}
};

class IndexBuffer {
public:
	std::vector<unsigned int> indices;

	IndexBuffer() = default;
	explicit IndexBuffer(std::vector<unsigned int> indices) : indices(std::move(indices)) {}
};

class Mesh {
public:
	std::vector<VertexBuffer> vertex_buffers;
	IndexBuffer index_buffer;
private:
	Mesh() = default;
public:
	static Mesh* create();
	static Mesh* create_rectangle();
	void prepare();
	void refresh();
};