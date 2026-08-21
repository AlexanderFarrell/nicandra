#pragma once

#include "../gpu.hpp"
#include "util/result.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/vulkan_raii.hpp"
#include <memory>
#include <vector>

namespace nc::hw::gpu::vulkan {

class VulkanGraphicsAPI: public nc::hw::gpu::GraphicsAPI {
private:
	vk::raii::Context context;
	vk::raii::Instance instance;
	std::vector<std::string> supported_instance_extensions;
	static Result<std::unique_ptr<VulkanGraphicsAPI>, std::string> create(Config& config);
public:
	bool uses_opengl_window_context() override;
};
