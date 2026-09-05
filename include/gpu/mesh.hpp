#pragma once

#include "assets/types.hpp"
#include <expected>
#include <vector>

class VertexBuffer {
public:
	std::vector<float> data;
	int elements_per_vertex;

	VertexBuffer() = default;
	explicit VertexBuffer(int elements_per_vertex)
	    : elements_per_vertex(elements_per_vertex) {}
	VertexBuffer(int elements_per_vertex, std::vector<float> data)
	    : data(std::move(data)), elements_per_vertex(elements_per_vertex) {}
};

class IndexBuffer {
public:
	std::vector<unsigned int> indices;

	IndexBuffer() = default;
	explicit IndexBuffer(std::vector<unsigned int> indices)
	    : indices(std::move(indices)) {}
};

class Mesh {
public:
	std::vector<VertexBuffer> vertex_buffers;
	IndexBuffer index_buffer;
private:
	GenIndex gpu_mesh_id;
	Mesh() = default;
public:
	static AssetID create();
	static AssetID create_rectangle();
};

class GPUMesh {
public:
	virtual std::expected<void, std::string> prepare(const Mesh &mesh) = 0;
	virtual std::expected<void, std::string> refresh(const Mesh &mesh) = 0;
	virtual void draw() = 0;
	virtual void destroy() = 0;
};
