#pragma once

#include "gpu/gpu.hpp"

class OpenGLGraphicsAPI: public GraphicsAPI {
	bool uses_opengl_window_context() override;
public:
	std::unique_ptr<Renderer> create_renderer(uint16_t width, uint16_t height) override;
};