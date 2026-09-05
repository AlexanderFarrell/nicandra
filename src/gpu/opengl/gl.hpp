#pragma once

#if OPENGL_SUPPORTED

#include <source_location>

#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#include "OpenGL/gl3.h"
#elif defined(__linux__)
#include <glad/glad.h>

#endif

void check_for_errors_gl(
    const std::source_location &location = std::source_location::current());

#endif
