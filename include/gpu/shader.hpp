#pragma once

#include <string>
#include <vector>
#include "util/data/slotmap.hpp"
#include "util/result.hpp"
#include <expected>

enum ShaderStage {
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	GEOMETRY_SHADER,
	COMPUTE_SHADER,
};

struct ShaderSource {
	ShaderStage stage;
	std::string source;
};

class Shader {
public:
	std::vector<ShaderSource> sources;
	GenIndex gpu_shader;
	Shader() = default;
	explicit Shader(std::vector<ShaderSource> sources): sources(std::move(sources)) {}
	virtual ~Shader() = default;
};

class GPUShader {
	virtual std::expected<void, std::string> init(const Shader& shader) = 0;
	virtual void destroy(const Shader& shader) = 0;
};
