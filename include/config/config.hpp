#pragma once

#include <string>
#include <cstdint>
#include <sys/types.h>

// TODO: While we can configure GPU APIs via config, we often want to:
//  1. Allow the user to choose which one they want.
//  2. Only support APIs on various platforms
//  3. Pick a default API when we don't care. I'm willing to bet most people
//     do not care about their word processor being in Metal or OpenGL.
//  4. Make this simple not complicated.

/**
* Configuration for creating a window.
*/
struct WindowConfig {
	// The text in the title bar of the window.
	std::string title = "Untitled Window";

	// The size left and right in pixels of the window.
	std::uint32_t width = 1280;

	// The size up and down in pixels of the window.
	std::uint32_t height = 720;
};

/**
* Various APIs for talking to the graphics card and drawing graphics.
*/
enum GraphicsAPIKind {
	// Open standard, essentially supported on almost any desktop. But
	// older and not as optimal CPU wise.
	GApiOpenGL,

	// Open standard, essentially supported on almost any desktop/mobile.
	// But older and not as optimal CPU wise.
	GApiOpenGLES,

	// Open standard, essentially supported on almost any modern desktop.
	// More optimized CPU wise.
	GApiVulkan,

	// Windows proprietary API, more optimized CPU wise.
	GApiDirectX12,

	// Apple proprietary API, more optimized CPU wise.
	GApiMetal,

	// Open standard, supported on most modern browsers. But older and not as
	// optimal CPU wise.
	GApiWebGL2,

	// Open standard *web browser* API, more optimized CPU wise. Internally
	// may use Vulkan/DirectX12/Metal
	GApiWebGPU,
};

/**
* Various APIs for talking to the graphics card for general computation.
*/
enum ComputeAPIKind {
	// Open standard. More support across desktops.
	CApiOpenCL,

	// Supported on NVIDIA cards.
	CUDA,

	// Open standard, more optimized CPU wise.
	CApiVulkan,

	// Windows proprietary API
	CApiDirectX12,

	// Apple proprietary API
	CApiMetal,

	// Browser based compute, more CPU optimized, less supported
	CApiWebGPU,
};

/**
* How do we talk to the graphics card for graphics and compute?
*/
struct GPUConfig {
	// Which API should we use to talk to the graphics card for graphics?
	GraphicsAPIKind graphics_api = GraphicsAPIKind::GApiOpenGL;

	// Which API should we use to talk to the graphics card for general compute.
	ComputeAPIKind compute_api = ComputeAPIKind::CApiOpenCL;
};

struct Version {
	uint32_t major_verison;
	uint32_t minor_version;
	uint32_t patch_version;
	std::string prefix = "";
	uint32_t unit_version;
};

/**
* Config for a Nicandra App/Game.
*/
struct Config {

	std::string application_name;

	Version application_version;


	const std::string engine_name = "Nicandra";
	const Version engine_version = {
		.major_verison = 0,
		.minor_version = 1,
		.patch_version = 0,
		.prefix = "dev",
		.unit_version = 1,
	};


	/**
	* Config for the main window. Spawn other windows as needed.
	*/
	WindowConfig window;

	/**
	* Config for APIs for the GPU.
	*/
	GPUConfig gpu;
};

