#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <GLFW/glfw3.h>
#include <vector>
#include "../util/data/slotmap.hpp"
#include "../util/result.hpp"
#include "config/config.hpp"

class Window {
private:
	WindowConfig _config;
	GLFWwindow *_glfw_window = nullptr;
	GenIndex _index;

	// Private. We do not allow the creation of windows outside the Window::Create() function
	Window(const WindowConfig& config, GLFWwindow* glfw_window);



	// Static members
	static SlotMap<Window> _active_windows;
	static std::vector<GenIndex> _windows_to_remove;

public:
	virtual ~Window();
	
	// Do not allow copying of the window handle.
	Window(Window &other) = delete;
	Window operator=(Window &other) = delete;
	
	// Move is allowed, internally
	Window(Window &&other);
	Window operator=(Window &&other);

	// Non-static (per window) methods
	std::uint32_t get_width();
	std::uint32_t get_height();
	const std::string &get_title();
	GLFWwindow* get_glfw_window();
	void set_size(const std::uint32_t width, const std::uint32_t height);
	void set_width(const std::uint32_t width);
	void set_height(const std::uint32_t height);
	void set_title(const std::string &title);
	void close();

	// Static (for all windows) methods
	static Result<GenIndex, std::string> create(const WindowConfig& config);
	static void destroy(const std::size_t index);
	static void destroy(const GenIndex &index);
	static std::optional<std::reference_wrapper<Window>> main_window();
	static std::optional<std::reference_wrapper<Window>> get(const std::size_t index);
	static std::optional<std::reference_wrapper<Window>> get(const GenIndex &index);
	static std::size_t get_active_window_count();

	static Result<void, std::string> setup_engine(const Config& config);
	static void update_engine();
	static void breakdown_engine();

	static SlotMap<Window>::Iterator begin();
	static SlotMap<Window>::Iterator end();
};

