#include "core/app.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include "window/window.hpp"
#include <cstddef>
#include <nicandra.hpp>

void start() {
	spdlog::info("Hello from Test Window");
	for (std::size_t i = 0; i < 100; i++) {
		WindowConfig config = {
			.width = 100,
			.height = 100,
			.title = "Window Two",
		};
		WindowManager::spawn(config);
	}
}

void end() {
	spdlog::info("Goodbye from Test Window");
}

int main() {
	spdlog::set_level(spdlog::level::debug);
  Nicandra::run_basic(start, end);
}