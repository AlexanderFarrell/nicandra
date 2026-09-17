#include "opengl_shader.hpp"
#include "gl.hpp"
#include <functional>
#include <spdlog/spdlog.h>
#include <vector>

static std::expected<GLuint, std::string>
shader_compile(const std::string &source, GLenum type);
static std::expected<GLenum, std::string>
shader_type_from_stage(ShaderStage stage);

std::expected<void, std::string> OpenGLShader::init(const Shader &shader) {
	this->destroy(shader);

	std::vector<GLuint> shader_ids;

	for (auto &shader_source : shader.sources) {
		auto result_type = shader_type_from_stage(shader_source.stage);
		if (!result_type.has_value()) {
			return std::unexpected(result_type.error());
		}

		auto result_compile =
		    shader_compile(shader_source.source, result_type.value());
		if (!result_compile.has_value()) {
			return std::unexpected(result_type.error());
		}
		GLuint shader_id = result_compile.value();
		shader_ids.push_back(shader_id);
	}

	this->shader_program = glCreateProgram();
	for (GLuint shader_id : shader_ids) {
		glAttachShader(this->shader_program, shader_id);
	}

	glLinkProgram(this->shader_program);
	check_for_errors_gl();

	std::function<void()> cleanup = [shader_ids, this]() {
		for (GLuint shader_id : shader_ids) {
			glDetachShader(this->shader_program, shader_id);
			glDeleteShader(shader_id);
		}
	};

	GLint status;
	glGetProgramiv(this->shader_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetProgramiv(this->shader_program, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> info_log(length);
		glGetProgramInfoLog(this->shader_program, length, &length,
		                    info_log.data());
		cleanup();
		glDeleteProgram(this->shader_program);
		return std::unexpected(std::string(info_log.data()));
	}

	cleanup();
	return {};
}

void OpenGLShader::destroy(const Shader &shader) {
	glDeleteProgram(this->shader_program);
}

static std::expected<GLuint, std::string>
shader_compile(const std::string &source, GLenum type) {
	GLuint shader = glCreateShader(type);
	const char *data = source.c_str();
	glShaderSource(shader, 1, (const GLchar *const *)&data, nullptr);
	glCompileShader(shader);
	check_for_errors_gl();

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> info_log(length);
		glGetShaderInfoLog(shader, length, &length, (GLchar *)info_log.data());
		return std::unexpected(std::string(info_log.data()));
	}
	return shader;
}

static std::expected<GLenum, std::string>
shader_type_from_stage(ShaderStage stage) {
	switch (stage) {
	case VERTEX_SHADER:
		return GL_VERTEX_SHADER;
	case FRAGMENT_SHADER:
		return GL_FRAGMENT_SHADER;
	case GEOMETRY_SHADER:
		return GL_GEOMETRY_SHADER;
	case COMPUTE_SHADER:
		return std::unexpected("OpenGL does not support compute shaders");
	default:
		return std::unexpected("Unknown shader stage");
	}
}
