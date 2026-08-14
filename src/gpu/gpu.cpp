#include "gpu/gpu.hpp"
#include <cstddef>
#include <memory>
#include <string>

// Private headers
#include "config/config.hpp"
#include "opengl.hpp"
#include "util/result.hpp"

std::unique_ptr<GPUGraphicsAPI> GPU::graphics = nullptr;
std::unique_ptr<GPUComputeAPI> GPU::compute = nullptr;

Result<void, std::string> GPU::setup_engine(const Config &config) {
	return GPU::switch_to_api(config.gpu.graphics_api);
}

void GPU::breakdown_engine() {
	GPU::graphics = nullptr;
	GPU::compute = nullptr;
}

Result<void, std::string> GPU::switch_to_api(const GraphicsAPIKind kind) {
	switch (kind) {
	case GApiOpenGL:
		GPU::graphics = std::make_unique<OpenGLGraphicsAPI>();
		break;
	default:
		return Result<void, std::string>::with_error(
		    "Unsupported graphics API"
		);
	}
	return Result<void, std::string>::with_ok();
}

GPUGraphicsAPI::~GPUGraphicsAPI() {
	
}