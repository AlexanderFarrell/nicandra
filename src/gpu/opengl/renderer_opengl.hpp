#pragma once

#include "gpu/gpu.hpp"

class OpenGLRenderer: public Renderer {
public:
	~OpenGLRenderer() override;
	OpenGLRenderer(uint16_t width, uint16_t height): Renderer(width, height) {}
	void setup() override;
	void breakdown() override;
	void render(GLFWwindow* window) override;
};