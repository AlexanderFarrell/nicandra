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

/**
* A portal into our app or game which has graphics, input, etc.
*/
class Window {
private:
	/**
	* The current settings of the window like width, height and title.
	*/
	WindowConfig _config;

	/**
	* A handle to a glfw window.
	*/
	GLFWwindow *_glfw_window = nullptr;

	/**
	* Which window is this amongst all the active windows? If _index.index is 0,
	* this is the main window.
	*/
	GenIndex _index;

	// Private. We do not allow the creation of windows outside the Window::Create() function
	Window(const WindowConfig& config, GLFWwindow* glfw_window);

	// Static members
	/**
	* Holds all the active windows in the app, indexed. 
	*/
	static SlotMap<Window> _active_windows;

	/**
	* Internally used when windows close. 
	*/
	static std::vector<GenIndex> _windows_to_remove;

public:
	virtual ~Window();
	
	// Do not allow copying of the window handle.
	Window(Window &other) = delete;
	Window operator=(Window &other) = delete;
	
	// Move is allowed
	Window(Window &&other);
	Window operator=(Window &&other);

	// Non-static (per window) methods

	/**
	* Returns the size in pixels left and right of the window.
	*/
	std::uint32_t get_width();

	/**
	* Returns the size in pixels up and down of the window.
	*/
	std::uint32_t get_height();

	/**
	* Returns the text in the top title bar of the window.
	*/
	const std::string &get_title();

	/**
	* Returns a handle to the GLFW window.
	*/
	GLFWwindow *get_glfw_window();

	/**
	* Changes the width and height of the window, immediately applying.
	*/
	void set_size(const std::uint32_t width, const std::uint32_t height);

	/**
	* Changes the width of the window, immediately applying.
	*/
	void set_width(const std::uint32_t width);

	/**
	* Changes the height of the window, immediately applying.
	*/
	void set_height(const std::uint32_t height);

	/**
	* Changes the text 
	*/
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

