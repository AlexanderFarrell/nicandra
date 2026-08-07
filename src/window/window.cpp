#include "window/window.hpp"
#include "GLFW/glfw3.h"
#include "core/engine.hpp"
#include "spdlog/spdlog.h"
#include "util/data/slotmap.hpp"
#include "util/result.hpp"
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <optional>
#include <string>
#include <vector>

SlotMap<Window> WindowManager::_windows;
std::vector<GenIndex> WindowManager::_windows_to_clear;

Result<Window, std::string> Window::Create(const WindowConfig &config,
                                           bool use_opengl) {
	// GLFW defaults to making an OpenGL context, but see... we might have
	// started with another renderer, then changed to OpenGL (re-creating
	// windows) thus we need to set back to OpenGL.
	if (use_opengl) {
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	} else {
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	GLFWwindow* glfw_window = glfwCreateWindow(
	    config.width, config.height, config.title.c_str(), nullptr, nullptr);
	if (!glfw_window) {
		return Result<Window, std::string>::with_error(
		    "Failed to create window"
		);
	}

	Window window;
	window.glfw_window = glfw_window;

	return Result<Window, std::string>::with_ok(window);
}


Window &WindowManager::main_window() {
	return WindowManager::_windows.get(0).value();
}

std::optional<std::reference_wrapper<Window>> WindowManager::get_by_id(std::size_t index) {
	return WindowManager::_windows.get(index);
}

std::optional<std::reference_wrapper<Window>> WindowManager::get_by_id(GenIndex &index) {
	return WindowManager::_windows.get(index);
}

Result<Window, std::string> WindowManager::spawn(WindowConfig &config) {
	Result<Window, std::string> result = Window::Create(config, true);
	if (!result.is_ok()) {
		return result;
	}
	auto index = WindowManager::_windows.add(std::move(result.get_value()));

	auto& w = WindowManager::get_by_id(index).value().get();
	w._index = index;
	return Result<Window, std::string>::with_ok(
	    WindowManager::get_by_id(index).value()
	);
}

void WindowManager::remove(std::size_t index) {
	WindowManager::_windows.remove(index);
}

void WindowManager::remove(GenIndex &index) {
	WindowManager::_windows.remove(index);
}

std::size_t WindowManager::get_window_count() {
	return WindowManager::_windows.size_active();
}

Result<void, std::string> WindowManager::setup() {
	// Initialize GLFW
	if (!glfwInit()) {
		return Result<void, std::string>::with_error(
		    "Failed to initialize GLFW library"
		);
	}

	// Set error handler
	glfwSetErrorCallback([](int error, const char *description) {
		spdlog::error("GLFW Error - Code: "
		              + std::to_string(error)
		              + " - "
		              + std::string(description));
	});

	// Start the main window
	WindowConfig config = WindowConfig{
	    .width = 1280,
	    .height = 720,
	    .title = "App",
	};
	Result<Window, std::string> main = WindowManager::spawn(config);
	if (!main.is_ok()) {
		return Result<void, std::string>::with_error(
			main.get_error()
		);
	}
	WindowManager::_windows.add(main.get_value());

	return Result<void, std::string>::with_ok();
}

void WindowManager::update() {
	for (auto& window : WindowManager::_windows) {
		if (glfwWindowShouldClose(window.glfw_window)) {
			WindowManager::_windows_to_clear.push_back(window._index);
		}

		glfwSwapBuffers(window.glfw_window);
		glfwPollEvents();
	}

	for (auto &index : WindowManager::_windows_to_clear) {
		WindowManager::_windows.remove(index);

		// Main window close closes the application
		if (index.index == 0) {
			// A hack, fix this.
			Engine::running = false;
		}		
	}
}

void WindowManager::breakdown() {
	// Invalidate and clean up all windows before the glfwTerminate call
	WindowManager::_windows.clear();

	// Breakdown GLFW
	glfwTerminate();
}

SlotMap<Window>::Iterator WindowManager::begin() {
	return WindowManager::_windows.begin();
}

SlotMap<Window>::Iterator WindowManager::end() {
	return WindowManager::_windows.end();
}