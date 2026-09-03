#pragma once

#include <string>
#include <vector>

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
	std::vector<ShaderSource> sources;
	GenIndex gpu_shader;
public:
	Shader() = default;
	explicit Shader(std::vector<ShaderSource> sources): sources(std::move(sources)) {}
	virtual ~Shader() = default;
};

class GPUShader {
	virtual void init(const Shader& shader) = 0;
};
