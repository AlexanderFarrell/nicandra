#include "core/app.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include "window/window.hpp"
#include <cstddef>
#include <nicandra.hpp>
#include <string>

/**
* Entrypoint once the engine starts.
*/
void start() {
	// Test that starting works.
	spdlog::info("Hello from Test Window");

	// Spawn a bunch of windows
	std::size_t window_count = 20;
	for (std::size_t i = 0; i < window_count; i++) {
		WindowConfig config = {
			.width = 200,
			.height = 100,
			.title = "Window " + std::to_string(i),
		};
		Window::create(config);
	}
}

/**
* Exit point when the engine gracefully shuts down.
*/
void end() {
	// Test that ending works.
	spdlog::info("Goodbye from Test Window");
}

/**
* Entry point for the app. 
*/
int main() {
	// We can set the debug
	spdlog::set_level(spdlog::level::debug);

	// Runs the engine with the given start and stop functions.
  	Nicandra::run_basic(start, end);
}