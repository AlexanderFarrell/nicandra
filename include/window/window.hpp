#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <GLFW/glfw3.h>
#include <vector>
#include "../util/data/slotmap.hpp"
#include "../util/result.hpp"

class Window {
private:
	std::string _title = "Untitled Window";
	std::uint32_t _width = 1280;
	std::uint32_t _height = 720;
	GLFWwindow *_glfw_window = nullptr;
	std::optional<GenIndex> _index = std::nullopt;
public:
	Window() = default;
	virtual ~Window();

	// This owns a window handle, so we don't want copy constructor or
	// assignment here. We will prevent it
	Window(const Window &other) = delete;
	Window operator=(const Window &other) = delete;

	// For move operations, we transfer the glfw_window to the new one
	Window(Window &&other);
	Window operator=(Window &&other);

	void open();
	void close();

	friend class WindowManager;
};


class WindowManager {
private:
	static SlotMap<Window> _windows;
	static std::vector<GenIndex> _windows_to_clear;
public:
	// Access
	static Window &main_window();
	static std::optional<std::reference_wrapper<Window>> get_by_id(std::size_t index);
	static std::optional<std::reference_wrapper<Window>> get_by_id(GenIndex &index);
	static std::size_t get_window_count();

	// Lifecycle
	static Result<void, std::string> setup();
	static void update();
	static void breakdown();

	// Iteration
	static SlotMap<Window>::Iterator begin();
	static SlotMap<Window>::Iterator end();
};

