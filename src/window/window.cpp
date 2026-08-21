#include "window/window.hpp"
#include "GLFW/glfw3.h"
#include "gpu/gpu.hpp"
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

SlotMap<Window> Window::_active_windows;
std::vector<GenIndex> Window::_windows_to_remove;

Window::Window(const WindowConfig &config, GLFWwindow* glfw_window) {
	this->_config = config;
	this->_glfw_window = glfw_window;
}

Window::~Window() {
	if (this->_glfw_window) {
		glfwDestroyWindow(this->_glfw_window);
	}
}

Window::Window(Window &&other) {
	this->_config = other._config;

	// Moves cause the other to no longer own the glfw_window
	this->_glfw_window = other._glfw_window;
	other._glfw_window = nullptr;
}

Window Window::operator=(Window &&other) {
	Window window(other._config, other._glfw_window);

	// Assignment move causes the other to no longer own the glfw_window
	other._glfw_window = nullptr;
	return window;
}

std::uint32_t Window::get_width() { return this->_config.width; }

std::uint32_t Window::get_height() { return this->_config.height; }

const std::string &Window::get_title() { return this->_config.title; }

GLFWwindow* Window::get_glfw_window() { return this->_glfw_window; }

void Window::set_size(const std::uint32_t width, const std::uint32_t height) {
	this->_config.width = width;
	this->_config.height = height;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowSize(this->_glfw_window, this->_config.width, this->_config.height);
	}
}

void Window::set_width(const std::uint32_t width) {
	this->_config.width = width;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowSize(this->_glfw_window, this->_config.width, this->_config.height);
	}
}

void Window::set_height(const std::uint32_t height) {
	this->_config.height = height;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowSize(this->_glfw_window, this->_config.width, this->_config.height);
	}
}

void Window::set_title(const std::string &title) {
	this->_config.title = title;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowTitle(this->_glfw_window, this->_config.title.c_str());
	}
}

void Window::close() {
	// Just remove self from the active windows
	Window::destroy(this->_index);
}

// Static methods

Result<GenIndex, std::string> Window::create(const WindowConfig &config) {
	// If in OpenGL mode, two things should happen:
	//  1. Let GLFW create the OpenGL Context.
	//  2. Share this OpenGL context (so things like gpu memory are common among
	//  all windows)
	//
	// To do this:
	//  1. We ask our GPU helper if it should use an OpenGL Window Context.
	//  2. we set the share to the main window's glfw handle only if we are
	//     in OpenGL mode.
	GLFWwindow* share = nullptr;

	if (GPU::graphics->uses_opengl_window_context()) {
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

		// Safely get the main window (we could be creating the main window, so
		// ignore if it doesn't exist). If we are making the main window now, we
		// keep at nullptr to let an OpenGL context be created.
		auto main_window = Window::main_window();
		if (main_window.has_value()) {
			share = main_window.value().get().get_glfw_window();
		}
	} else {
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	GLFWwindow *glfw_window = glfwCreateWindow(
	    config.width, config.height, config.title.c_str(), nullptr, share);

	if (!glfw_window) {
		return Result<GenIndex, std::string>::with_error(
		    "Failed to create window"
		);
	}

	Window window(config, glfw_window);
	GenIndex index = Window::_active_windows.add(std::move(window));

	// Add the index to the window
	Window::_active_windows.get(index)->get()._index = index;

	return Result<GenIndex, std::string>::with_ok(index);
}

void Window::destroy(const std::size_t index) {
	Window::_active_windows.remove(index);
}

void Window::destroy(const GenIndex &index) {
	Window::_active_windows.remove(index);
}

std::optional<std::reference_wrapper<Window>> Window::main_window() {
	return Window::get(GenIndex{
	    .index = 0,
	    .generation = 0
	});
}

std::optional<std::reference_wrapper<Window>> Window::get(const std::size_t index) {
	return Window::_active_windows.get(index);
}

std::optional<std::reference_wrapper<Window>>
Window::get(const GenIndex &index) {
	return Window::_active_windows.get(index);
}

std::size_t Window::get_active_window_count() {
	return Window::_active_windows.size_active();
}

Result<void, std::string> Window::setup_engine(const Config& config) {
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

	auto result = Window::create(config.window);
	if (result.is_err()) {
		return Result<void, std::string>::with_error(
		    result.get_error()
		);
	};
	return Result<void, std::string>::with_ok();
}

void Window::update_engine() {
	for (auto &window : Window::_active_windows) {
		if (glfwWindowShouldClose(window._glfw_window)) {
			Window::_windows_to_remove.push_back(window._index);
		}
	}
	glfwPollEvents();
	if (Window::_windows_to_remove.size() > 0) {
		for (auto &index : Window::_windows_to_remove) {
			Window::destroy(index);

			// If main window closes, we close the app
			if (index.index == 0) {
				Engine::running = false;
			}
		}
		Window::_windows_to_remove.clear();
	}
}

void Window::breakdown_engine() {
	// Destroy all windows before the glfwTerminate call
	Window::_active_windows.clear();

	// Breakdown GLFW
	glfwTerminate();
}

SlotMap<Window>::Iterator Window::begin() {
	return Window::_active_windows.begin();
}

SlotMap<Window>::Iterator Window::end() {
	return Window::_active_windows.end();
}
