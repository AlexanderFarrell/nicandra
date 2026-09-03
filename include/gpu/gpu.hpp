#pragma once

// We separate GPU APIs (Metal, DirectX 12, OpenGL, Vulkan, etc.) from
// graphics code. Reason being is that other things need to know how
// we talk to the GPU other than visuals, for example, the asset
// manager can now buffer meshes and load shaders... without the graphics
// engine caring. Or windows can be set up appropriately before the visuals.
//
// Similarly, this gives us a nice API for accessing the graphics card.
//
// One other nice thing is we can decide what graphics API we are using
// before we even initialize it.

#include "../core/config.hpp"
#include "util/result.hpp"
#include "api.hpp"
#include <memory>
#include <string>


/**
* Handles calling the graphics card.
*/
class GPU {
public:
	/**
	* Draws graphics to the screen using the GPU. 
	*/
	static std::unique_ptr<GraphicsAPI> graphics;

	/**
	* Performs highly parallel compute on the GPU.
	*/
	static std::unique_ptr<ComputeAPI> compute;

	static Result<void, std::string> switch_to_api(const GraphicsAPIKind kind);

	/**
	* Called by App to initialize a graphics and optionally compute GPU APIs. 
	*/
	static Result<void, std::string> setup_engine(const Config &config);

	/**
	* Called by the App to breakdown (gracefully) the GPU resources.
	*/
	static void breakdown_engine();
};
