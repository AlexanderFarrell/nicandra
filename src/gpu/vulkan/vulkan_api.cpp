#if VULKAN_SUPPORTED
#include "vulkan_api.hpp"
#include "core/app.hpp"
#include "core/config.hpp"
#include "util/result.hpp"
#include <memory>


#include <vulkan/vulkan_raii.hpp>

// Result<std::unique_ptr<VulkanGraphicsAPI>, std::string>
// VulkanGraphicsAPI::create(AppInfo& info) { 	std::string app_version =
// info.app_version.to_string(); 	std::string engine_version =
// info.config.engine_version.to_string();

// 	constexpr vk::ApplicationInfo app_info{
// 		.pApplicationName = info.app_name.c_str(),
// 		.applicationVersion = app_version.c_str(),
// 		.pEngineName = info.config.engine_name.c_str(),
// 		.engineVersion = engine_version.c_str(),
// 		.pNext = nullptr,
// 	};

// 	vk::InstanceCreateInfo create_info{
// 		.pApplicationInfo = &app_info,
// 	};

// 	vk::raii::Context context;
// 	vk::raii::Instance instance = vk::raii::Instance(context, create_info);
// }
#endif
