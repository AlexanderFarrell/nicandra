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
	std::uint32_t width = 1280;
	std::uint32_t height = 720;
	std::string title = "Untitled Window";
};

class Window {
private:
	GenIndex _index;
	GLFWwindow *glfw_window = nullptr;

	static Result<Window, std::string> Create(const WindowConfig& config, bool use_opengl, GLFWwindow* share = nullptr);

public:
	Window() = default;
	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;
	Window(Window&& window);
	
	virtual ~Window();

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
	static Result<Window, std::string> spawn(WindowConfig& config);
	static void remove(std::size_t index);
	static void remove(GenIndex &index);
	static std::size_t get_window_count();

	// Lifecycle
	static Result<void, std::string> setup();
	static void update();
	static void breakdown();

	// Iteration
	static SlotMap<Window>::Iterator begin();
	static SlotMap<Window>::Iterator end();
};

