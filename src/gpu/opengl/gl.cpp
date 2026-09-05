#include "gl.hpp"
#include <source_location>
#include <sstream>
#include "core/app.hpp"

static std::string get_string_for_opengl_error_code(GLenum code);

void check_for_errors_gl(const std::source_location& location) {
	GLenum code = glGetError();
	if (code != GL_NO_ERROR) {
		std::stringstream ss;
		ss << "Graphics Error\n - Code: "
		    << std::to_string(code)
		    << " - File: "
		    << location.file_name()
		    << "\n - Line: "
		    << std::to_string(location.line())
		    << "\n - Message: "
		    << get_string_for_opengl_error_code(code);
		std::string message = ss.str();
		App::panic(message);
	}
}

static std::string get_string_for_opengl_error_code(GLenum code) {
	switch (code) {
	case GL_INVALID_ENUM:
		return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:
		return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:
		return "GL_INVALID_OPERATION";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "GL_INVALID_FRAMEBUFFER_OPERATION";
	case GL_OUT_OF_MEMORY:
		return "GL_OUT_OF_MEMORY";
	default:
		return "GL_UNKNOWN_ERROR";
	}
}
