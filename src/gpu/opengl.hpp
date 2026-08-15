#pragma once

#include "gpu/gpu.hpp"

class OpenGLGraphicsAPI: public GPUGraphicsAPI {
	bool uses_opengl_window_context() override;
};