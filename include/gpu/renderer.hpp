#pragma once

#include "../util/data/slotmap.hpp"
#include "GLFW/glfw3.h"
#include "drawable.hpp"
#include <cstdint>
#include <glm/glm.hpp>
#include <memory>

class Renderer {
protected:

	bool wireframe_enabled = false;
	glm::vec3 clear_color = glm::vec3(0.5, 0.5, 0.5);
	uint16_t width;
	uint16_t height;

	Renderer(uint16_t width, uint16_t height);

public:
	SlotMap<Drawable> drawables;

	virtual ~Renderer() = default;
	/**
	 * Initializes the renderer. Override this to implement behavior per
	 * graphics API.
	 */
	virtual void setup() = 0;

	/**
	 * Breaks down the given renderer. Override this to implement behavior per
	 * graphics API.
	 */
	virtual void breakdown() = 0;

	/**
	 * Draws a single frame, running the entire renderer pipeline for clear,
	 * drawing objects, etc.
	 */
	virtual void render(GLFWwindow *window) = 0;

	friend class GraphicsAPI;
};
