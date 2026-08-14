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

SlotMap<Window> Window::_active_windows;
std::vector<GenIndex> Window::_windows_to_remove;

std::uint32_t Window::get_width() { return this->config.width; }

std::uint32_t Window::get_height() { return this->config.height; }

const std::string &Window::get_title() { return this->config.title; }

void Window::set_size(const std::uint32_t width, const std::uint32_t height) {
	this->config.width = width;
	this->config.height = height;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowSize(this->_glfw_window, this->config.width, this->config.height);
	}
}

void Window::set_width(const std::uint32_t width) {
	this->config.width = width;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowSize(this->_glfw_window, this->config.width, this->config.height);
	}
}

void Window::set_height(const std::uint32_t height) {
	this->config.height = height;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowSize(this->_glfw_window, this->config.width, this->config.height);
	}
}

void Window::set_title(const std::string &title) {
	this->config.title = title;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowTitle(this->_glfw_window, this->config.title.c_str());
	}
}


// SlotMap<Window> WindowManager::_windows;
// std::vector<GenIndex> WindowManager::_windows_to_clear;

// Window::~Window() {
// 	if (this->_glfw_window != nullptr) {
// 		glfwDestroyWindow(this->_glfw_window);
// 	}
// 	this->_index = std::nullopt;
// }

// Window::Window(Window &&other)
//     : _title(other._title), _width(other._width), _height(other._height),
//       _index(other._index) {
// 	// Take its handle, and invalidate the other (so it doesn't destroy the
// 	// window)
// 	this->_glfw_window = other._glfw_window;
// 	other._glfw_window = nullptr;
// }

// Window Window::operator=(Window &&other) {
// 	Window window;
// 	window._title = other._title;
// 	window._width = other._width;
// 	window._height = other._height;
// 	window._index = other._index;

// 	window._glfw_window = other._glfw_window;
// 	other._glfw_window = nullptr;
// 	return window;
// }

// Window& WindowManager::main_window() {
// 	return WindowManager::_windows.get(0)->get();
// }

// std::optional<std::reference_wrapper<Window>> WindowManager::get_by_id(std::size_t index) {
// 	return WindowManager::_windows.get(index);
// }

// std::optional<std::reference_wrapper<Window>>
// WindowManager::get_by_id(GenIndex &index) {
// 	return WindowManager::_windows.get(index);
// }

// std::size_t WindowManager::get_window_count() {
// 	return WindowManager::_windows.size_active();
// }



// Result<Window, std::string> Window::Create(const WindowConfig &config,
//                                            bool use_opengl,
//                                            GLFWwindow* share) {
// 	// GLFW defaults to making an OpenGL context, but see... we might have
// 	// started with another renderer, then changed to OpenGL (re-creating
// 	// windows) thus we need to set back to OpenGL.
// 	if (use_opengl) {
// 		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
// 	} else {
// 		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
// 	}

// 	GLFWwindow* glfw_window = glfwCreateWindow(
// 	    config.width, config.height, config.title.c_str(), nullptr, share);
// 	if (!glfw_window) {
// 		return Result<Window, std::string>::with_error(
// 		    "Failed to create window"
// 		);
// 	}

// 	Window window;
// 	window.glfw_window = glfw_window;

// 	return Result<Window, std::string>::with_ok(std::move(window));
// }

// Window::~Window() {
// 	if (this->glfw_window != nullptr) {
// 		glfwDestroyWindow(this->glfw_window);
// 	}
// }

// Window::Window(Window &&window) {
// 	this->glfw_window = window.glfw_window;
// 	this->_index = window._index;
// 	window.glfw_window = nullptr;
// }


// Window &WindowManager::main_window() {
// 	return WindowManager::_windows.get(0).value();
// }

// std::optional<std::reference_wrapper<Window>> WindowManager::get_by_id(std::size_t index) {
// 	return WindowManager::_windows.get(index);
// }

// std::optional<std::reference_wrapper<Window>> WindowManager::get_by_id(GenIndex &index) {
// 	return WindowManager::_windows.get(index);
// }

// Result<Window, std::string> WindowManager::spawn(WindowConfig &config) {
// 	bool opengl = true;
// 	GLFWwindow *share = (opengl && WindowManager::_windows.size_active() > 0)
// 	    ? WindowManager::_windows.get(0).value().get().glfw_window
// 	      : nullptr;

// 	Result<Window, std::string> result = Window::Create(config, opengl, share);
// 	if (!result.is_ok()) {
// 		return result;
// 	}
// 	auto index = WindowManager::_windows.add(std::move(result.get_value()));

// 	auto& w = WindowManager::get_by_id(index).value().get();
// 	w._index = index;
// 	return Result<Window, std::string>::with_ok(
// 	    WindowManager::get_by_id(index).value()
// 	);
// }

// void WindowManager::remove(std::size_t index) {
// 	WindowManager::_windows.remove(index);
// }

// void WindowManager::remove(GenIndex &index) {
// 	WindowManager::_windows.remove(index);
// }

// std::size_t WindowManager::get_window_count() {
// 	return WindowManager::_windows.size_active();
// }

// Result<void, std::string> WindowManager::setup() {
// 	// Initialize GLFW
// 	if (!glfwInit()) {
// 		return Result<void, std::string>::with_error(
// 		    "Failed to initialize GLFW library"
// 		);
// 	}

// 	// Set error handler
// 	glfwSetErrorCallback([](int error, const char *description) {
// 		spdlog::error("GLFW Error - Code: "
// 		              + std::to_string(error)
// 		              + " - "
// 		              + std::string(description));
// 	});

// 	// Start the main window
// 	WindowConfig config = WindowConfig{
// 	    .width = 1280,
// 	    .height = 720,
// 	    .title = "App",
// 	};
// 	Result<Window, std::string> main = WindowManager::spawn(config);
// 	if (!main.is_ok()) {
// 		return Result<void, std::string>::with_error(
// 			main.get_error()
// 		);
// 	}

// 	return Result<void, std::string>::with_ok();
// }

// void WindowManager::update() {
// 	for (auto& window : WindowManager::_windows) {
// 		if (glfwWindowShouldClose(window.glfw_window)) {
// 			WindowManager::_windows_to_clear.push_back(window._index);
// 		}

// 		glfwSwapBuffers(window.glfw_window);
// 	}
// 	glfwPollEvents();

// 	if (WindowManager::_windows_to_clear.size() > 0) {
// 		for (auto &index : WindowManager::_windows_to_clear) {
// 			WindowManager::_windows.remove(index);

// 			// Main window close closes the application
// 			if (index.index == 0) {
// 				// A hack, fix this.
// 				Engine::running = false;
// 			}		
// 		}
// 		WindowManager::_windows_to_clear.clear();
// 	}
// }

// void WindowManager::breakdown() {
// 	// Invalidate and clean up all windows before the glfwTerminate call
// 	WindowManager::_windows.clear();

// 	// Breakdown GLFW
// 	glfwTerminate();
// }

// SlotMap<Window>::Iterator WindowManager::begin() {
// 	return WindowManager::_windows.begin();
// }

// SlotMap<Window>::Iterator WindowManager::end() {
// 	return WindowManager::_windows.end();
// }