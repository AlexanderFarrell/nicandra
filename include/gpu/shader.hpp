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
public:
	Shader();
	Shader(const std::vector<ShaderSource> &sources);
	virtual ~Shader();
};
