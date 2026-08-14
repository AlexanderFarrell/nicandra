#pragma once

#include <string>
#include <cstdint>

struct WindowConfig {
	std::string title = "Untitled Window";
	std::uint32_t width = 1280;
	std::uint32_t height = 720;
};

enum GraphicsAPIKind {
	GApiOpenGL,
	GApiVulkan,
	GApiDirectX12,
	GApiMetal,
};

enum ComputeAPIKind {
	CApiOpenCL,
	CApiVulkan,
	CApiDirectX12,
	CApiMetal,
};

struct GPUConfig {
	GraphicsAPIKind graphics_api = GraphicsAPIKind::GApiOpenGL;
};


struct Config {
	WindowConfig window;
	GPUConfig gpu;
};

