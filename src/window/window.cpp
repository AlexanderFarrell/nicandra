#include "window/window.hpp"
#include "../gpu/opengl/gl.hpp"
#include "GLFW/glfw3.h"
#include "core/app.hpp"
#include "gpu/gpu.hpp"
#include "spdlog/spdlog.h"
#include "util/data/slotmap.hpp"
#include <functional>
#include <optional>
#include <string>
#include <vector>

SlotMap<Window> WindowManager::_active_windows;
std::vector<GenIndex> WindowManager::_windows_to_remove;

Window::Window(const WindowConfig &config, GLFWwindow *glfw_window) {
	this->_config = config;
	this->_glfw_window = glfw_window;
	this->_renderer =
	    GPU::graphics->create_renderer(config.width, config.height);
	this->_renderer->setup();
}

Window::~Window() {
	if (this->_renderer) {
		this->_renderer->breakdown();
	}

	if (this->_glfw_window) {
		glfwDestroyWindow(this->_glfw_window);
	}
}

Window::Window(Window &&other) {
	this->_config = other._config;

	// Moves cause the other to no longer own the glfw_window
	this->_glfw_window = other._glfw_window;
	this->_renderer = std::move(other._renderer);
	other._glfw_window = nullptr;
}

Window Window::operator=(Window &&other) {
	Window window(other._config, other._glfw_window);
	window._renderer = std::move(other._renderer);

	// Assignment move causes the other to no longer own the glfw_window
	other._glfw_window = nullptr;
	return window;
}

std::uint32_t Window::get_width() { return this->_config.width; }

std::uint32_t Window::get_height() { return this->_config.height; }

const std::string &Window::get_title() { return this->_config.title; }

GLFWwindow *Window::get_glfw_window() { return this->_glfw_window; }

void Window::set_size(const std::uint32_t width, const std::uint32_t height) {
	this->_config.width = width;
	this->_config.height = height;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowSize(this->_glfw_window, this->_config.width,
		                  this->_config.height);
	}
}

void Window::set_width(const std::uint32_t width) {
	this->_config.width = width;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowSize(this->_glfw_window, this->_config.width,
		                  this->_config.height);
	}
}

void Window::set_height(const std::uint32_t height) {
	this->_config.height = height;
	if (this->_glfw_window != nullptr) {
		glfwSetWindowSize(this->_glfw_window, this->_config.width,
		                  this->_config.height);
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
	WindowManager::destroy(this->_index);
}

// Static methods

std::expected<GenIndex, std::string>
WindowManager::create(const WindowConfig &config) {
	// If in OpenGL mode, two things should happen:
	//  1. Let GLFW create the OpenGL Context.
	//  2. Share this OpenGL context (so things like gpu memory are common among
	//  all windows)
	//
	// To do this:
	//  1. We ask our GPU helper if it should use an OpenGL Window Context.
	//  2. we set the share to the main window's glfw handle only if we are
	//     in OpenGL mode.
	GLFWwindow *share = nullptr;

	if (GPU::graphics->uses_opengl_window_context()) {
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);


		// Safely get the main window (we could be creating the main window, so
		// ignore if it doesn't exist). If we are making the main window now, we
		// keep at nullptr to let an OpenGL context be created.
		auto main_window = WindowManager::main_window();
		if (main_window.has_value()) {
			share = main_window.value().get().get_glfw_window();
		} else {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
	} else {
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	if (config.is_floating) {
		glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	} else {
		glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
	}

	GLFWwindow *glfw_window = glfwCreateWindow(
	    config.width, config.height, config.title.c_str(), nullptr, share);

	if (!glfw_window) {
		return std::unexpected("Failed to create window");
	}

	if (GPU::graphics->uses_opengl_window_context() &&
	    !WindowManager::main_window().has_value()) {
		glfwMakeContextCurrent(glfw_window);
	}

	Window window(config, glfw_window);
	GenIndex index = WindowManager::_active_windows.add(std::move(window));

	// Add the index to the window
	WindowManager::_active_windows.get(index)->get()._index = index;

	return {};
}

void WindowManager::destroy(const std::size_t index) {
	WindowManager::_active_windows.remove(index);
}

void WindowManager::destroy(const GenIndex &index) {
	WindowManager::_active_windows.remove(index);
}

std::optional<std::reference_wrapper<Window>> WindowManager::main_window() {
	return WindowManager::get(GenIndex{.index = 0, .generation = 0});
}

std::optional<std::reference_wrapper<Window>>
WindowManager::get(const std::size_t index) {
	return WindowManager::_active_windows.get(index);
}

std::optional<std::reference_wrapper<Window>>
WindowManager::get(const GenIndex &index) {
	return WindowManager::_active_windows.get(index);
}

std::size_t WindowManager::get_active_window_count() {
	return WindowManager::_active_windows.size_active();
}

std::expected<void, std::string>
WindowManager::setup_engine(const Config &config) {
	// Initialize GLFW
	if (!glfwInit()) {
		return std::unexpected("Failed to initialize GLFW library");
	}

	// Set error handler
	glfwSetErrorCallback([](int error, const char *description) {
		spdlog::error("GLFW Error - Code: " + std::to_string(error) + " - " +
		              std::string(description));
	});

	auto result = WindowManager::create(config.window);
	if (!result.has_value()) {
		return std::unexpected(result.error());
	};
	return {};
}

void WindowManager::update_engine() {
	for (auto &window : WindowManager::_active_windows) {
		if (glfwWindowShouldClose(window._glfw_window)) {
			WindowManager::_windows_to_remove.push_back(window._index);
		}
		window._renderer->render(window._glfw_window);
		glfwSwapBuffers(window._glfw_window);
	}
	glfwPollEvents();
	if (WindowManager::_windows_to_remove.size() > 0) {
		for (auto &index : WindowManager::_windows_to_remove) {
			WindowManager::destroy(index);

			// If main window closes, we close the app
			if (index.index == 0) {
				App::stop();
			}
		}
		WindowManager::_windows_to_remove.clear();
	}
}

void WindowManager::breakdown_engine() {
	// Destroy all windows before the glfwTerminate call
	WindowManager::_active_windows.clear();

	// Breakdown GLFW
	glfwTerminate();
}

SlotMap<Window>::Iterator WindowManager::begin() {
	return WindowManager::_active_windows.begin();
}

SlotMap<Window>::Iterator WindowManager::end() {
	return WindowManager::_active_windows.end();
}
