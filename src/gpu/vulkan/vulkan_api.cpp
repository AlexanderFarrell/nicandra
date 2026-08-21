#include "gpu/vulkan/vulkan_api.hpp"
#include "config/config.hpp"
#include "util/result.hpp"
#include <memory>
#include <vulkan/vulkan_raii.hpp>

using namespace nc::hw::gpu::vulkan;

Result<std::unique_ptr<VulkanGraphicsAPI>, std::string> VulkanGraphicsAPI::create(Config& config) {
	constexpr vk::ApplicationInfo app_info{
		.pApplicationName = config.application_name.c_str(),
		.applicationVersion = config.application_version.unit_version,
		.pEngineName = config.engine_name.c_str(),
		.engineVersion = config.engine_version.unit_version,
	};

	vk::InstanceCreateInfo create_info{
		.pApplicationInfo = &app_info,
	};
	
	vk::raii::Context context;
	vk::raii::Instance instance = vk::raii::Instance(context, create_info);
}