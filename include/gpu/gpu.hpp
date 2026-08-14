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

#include <cstddef>
#include <memory>
#include <string>
#include "util/result.hpp"
#include "config/config.hpp"

class GPUGraphicsAPI;
class GPUComputeAPI;

class GPU {
public:
	static std::unique_ptr<GPUGraphicsAPI> graphics;
	static std::unique_ptr<GPUComputeAPI> compute;

	static Result<void, std::string> setup_engine(const Config& config);
	static void breakdown_engine();

	static Result<void, std::string> switch_to_api(const GraphicsAPIKind kind);
};

class GPUGraphicsAPI {
public:
	virtual ~GPUGraphicsAPI();
	virtual bool uses_opengl_window_context() = 0;
};

class GPUComputeAPI {};