#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <GLFW/glfw3.h>
#include <vector>
#include "../util/data/slotmap.hpp"
#include "../util/result.hpp"

struct WindowConfig {
	std::string title = "Untitled Window";
	std::uint32_t width = 1280;
	std::uint32_t height = 720;
};

class Window {
private:
	WindowConfig config;
	GLFWwindow *_glfw_window = nullptr;

	// Private. We do not allow the creation of windows outside the Window::Create() function
	Window(WindowConfig& config);
	virtual ~Window();

	// Static members
	static SlotMap<Window> _active_windows;
	static std::vector<GenIndex> _windows_to_remove;

public:
	// Non-static (per window) methods
	std::uint32_t get_width();
	std::uint32_t get_height();
	const std::string& get_title();
	void set_size(const std::uint32_t width, const std::uint32_t height);
	void set_width(const std::uint32_t width);
	void set_height(const std::uint32_t height);
	void set_title(const std::string &title);
	void close();

	// Static (for all windows) methods
	static GenIndex create(const WindowConfig& config);
	static void destroy(const std::size_t index);
	static void destroy(const GenIndex& index);
	static std::optional<std::reference_wrapper<Window>> get(const std::size_t index);
	static std::optional<std::reference_wrapper<Window>> get(const GenIndex &index);
	static std::size_t get_active_window_count();

	static void setup_engine();
	static void update_engine();
	static void breakdown_engine();

	static SlotMap<Window>::Iterator begin();
	static SlotMap<Window>::Iterator end();
};



// class Window {
// private:
// 	std::string _title = "Untitled Window";
// 	std::uint32_t _width = 1280;
// 	std::uint32_t _height = 720;
// 	GLFWwindow *_glfw_window = nullptr;
// 	std::optional<GenIndex> _index = std::nullopt;
// public:
// 	Window() = default;
// 	virtual ~Window();

// 	// This owns a window handle, so we don't want copy constructor or
// 	// assignment here. We will prevent it
// 	Window(const Window &other) = delete;
// 	Window operator=(const Window &other) = delete;

// 	// For move operations, we transfer the glfw_window to the new one
// 	Window(Window &&other);
// 	Window operator=(Window &&other);

// 	friend class WindowManager;
// };


// class WindowManager {
// private:
// 	static SlotMap<Window> _windows;
// 	static std::vector<GenIndex> _windows_to_clear;
// public:
// 	// Access
// 	static Window &main_window();
// 	static std::optional<std::reference_wrapper<Window>> get_by_id(std::size_t index);
// 	static std::optional<std::reference_wrapper<Window>> get_by_id(GenIndex &index);
// 	static std::size_t get_window_count();
// 	static Result<void, std::string> open(Window window);
// 	static Result<void, std::string> close(GenIndex& index);

// 	// Lifecycle
// 	static Result<void, std::string> setup();
// 	static void update();
// 	static void breakdown();

// 	// Iteration
// 	static SlotMap<Window>::Iterator begin();
// 	static SlotMap<Window>::Iterator end();
// };

