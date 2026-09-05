#pragma once

#include "gpu/gpu.hpp"
#include "core/app.hpp"
#include "util/result.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/vulkan_raii.hpp"
#include <memory>
#include <vector>


class VulkanGraphicsAPI: public GraphicsAPI {
private:
	vk::raii::Context context;
	vk::raii::Instance instance;
	std::vector<std::string> supported_instance_extensions;
	static std::expected<std::unique_ptr<VulkanGraphicsAPI>, std::string> create(AppInfo& info);
public:
	bool uses_opengl_window_context() override;
};
