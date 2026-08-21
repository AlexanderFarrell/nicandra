#pragma once

#include "gpu/gpu.hpp"

class OpenGLGraphicsAPI: public GraphicsAPI {
	bool uses_opengl_window_context() override;
};