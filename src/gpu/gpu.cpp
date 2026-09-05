#include "gpu/gpu.hpp"
#include <memory>
#include <string>
#include <expected>

// Private headers
#include "opengl/opengl.hpp"

std::unique_ptr<GraphicsAPI> GPU::graphics = nullptr;
std::unique_ptr<ComputeAPI> GPU::compute = nullptr;

std::expected<void, std::string> GPU::setup_engine(const Config &config) {
	return GPU::switch_to_api(config.gpu.graphics_api);
}

void GPU::breakdown_engine() {
	GPU::graphics = nullptr;
	GPU::compute = nullptr;
}

std::expected<void, std::string> GPU::switch_to_api(const GraphicsAPIKind kind) {
	switch (kind) {
	case GApiOpenGL:
		GPU::graphics = std::make_unique<OpenGLGraphicsAPI>();
		break;
	default:
		return std::unexpected("Unsupported graphics API");
	}
	return {};
}

GraphicsAPI::~GraphicsAPI() {
	
}