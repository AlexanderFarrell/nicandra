#pragma once

#include "gl.hpp"
#include "gpu/shader.hpp"
#include "util/result.hpp"

class OpenGLShader : public GPUShader {
private:
	GLuint shader_program;
public:
	std::expected<void, std::string> init(const Shader &shader) override;
	void destroy(const Shader &shader) override;
};
