#include "core/app.hpp"
#include "gpu/gpu.hpp"
#include "spdlog/spdlog.h"
#include "window/window.hpp"

#include <chrono>
#include <csignal>
#include <cstdlib>
#include <string>
#include <thread>


AppInfo App::info;
bool App::running;

void handle_signal(int signal) {
	switch (signal) {
	case SIGINT:  // User request to stop gracefully
	case SIGTERM: // General request to stop gracefully, such as from another
	              // program.
		App::stop();
		break;
	default:
		App::panic("Unhandled signal: " + std::to_string(signal));
	}
}

void App::run(const AppInfo &info) {
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);

	App::running = true;
	auto result = GPU::setup_engine(info.config);
	if (!result.has_value()) {
		App::panic(result.error());
	}

	result = WindowManager::setup_engine(info.config);
	if (!result.has_value()) {
		App::panic(result.error());
	}

	spdlog::debug("Running " + info.app_name);

	info.on_start();

	while (App::running) {
		WindowManager::update_engine();
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}

	info.on_end();

	WindowManager::breakdown_engine();
	GPU::breakdown_engine();

	spdlog::debug("Stopped " + info.app_name);
}

void App::stop() {
	// Sets to false to gracefully shutdown next game loop.
	App::running = false;
}

void App::panic(const std::string &message) {
	spdlog::error(message);
	std::abort();
}

bool App::is_running() { return App::running; }
