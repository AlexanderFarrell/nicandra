#include "core/app.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include "window/window.hpp"
#include <cstddef>
#include <nicandra.hpp>
#include <string>

void start() {
	spdlog::info("Hello from Test Window");
	for (std::size_t i = 0; i < 20; i++) {
		WindowConfig config = {
			.width = 200,
			.height = 100,
			.title = "Window " + std::to_string(i),
		};
		Window::create(config);
	}
}

void end() {
	spdlog::info("Goodbye from Test Window");
}

int main() {
	spdlog::set_level(spdlog::level::debug);
  Nicandra::run_basic(start, end);
}