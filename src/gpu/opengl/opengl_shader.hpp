#pragma once

#include "gpu/shader.hpp"
#include "util/result.hpp"

class OpenGLShader: public GPUShader {
	std::expected<void, std::string> init(const Shader &shader) override;
	void destroy(const Shader& shader) override;
};