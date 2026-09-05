#pragma once

#include <cstddef>
#include <cstdint>
#include <expected>
#include <functional>
#include <optional>

#include "../core/config.hpp"
#include "../util/data/slotmap.hpp"
#include "gpu/renderer.hpp"
#include <GLFW/glfw3.h>
#include <vector>

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
	 * Which window is this amongst all the active windows? If _index.index is
	 * 0, this is the main window.
	 */
	GenIndex _index;

	std::unique_ptr<Renderer> _renderer = nullptr;

	// Private. We do not allow the creation of windows outside the
	// Window::Create() function
	Window(const WindowConfig &config, GLFWwindow *glfw_window);

public:
	virtual ~Window();

	// Do not allow copying of the window handle.
	Window(Window &other) = delete;
	Window operator=(Window &other) = delete;

	// Move is allowed
	Window(Window &&other);
	Window operator=(Window &&other);

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
	 * Changes the text of the title bar at the top.
	 */
	void set_title(const std::string &title);

	/**
	 * Closes the window.
	 */
	void close();

	friend class WindowManager;
};

class WindowManager {
private:
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

	/**
	 * Creates a new window. Returns the GenIndex if successful, or error string
	 * if not.
	 */
	static std::expected<GenIndex, std::string>
	create(const WindowConfig &config);

	/**
	 * Closes and destroys the given window. Safer to pass a GenIndex.
	 */
	static void destroy(const std::size_t index);

	/**
	 * Closes and destroys the given window safely.
	 */
	static void destroy(const GenIndex &index);

	/**
	 * Gets the main window (window at index 0)
	 */
	static std::optional<std::reference_wrapper<Window>> main_window();

	/**
	 * Gets the window at the given index. Safer to pass a GenIndex if you can.
	 */
	static std::optional<std::reference_wrapper<Window>>
	get(const std::size_t index);

	/**
	 * Gets the window at the given index.
	 */
	static std::optional<std::reference_wrapper<Window>>
	get(const GenIndex &index);

	/**
	 * Gets the number of open windows.
	 */
	static std::size_t get_active_window_count();

	/**
	 * Called by the engine to setup GLFW.
	 */
	static std::expected<void, std::string> setup_engine(const Config &config);

	/**
	 * Called by the engine to update all windows and poll events.
	 */
	static void update_engine();

	/**
	 * Called by the engine to breakdown windows and GLFW.
	 */
	static void breakdown_engine();

	/**
	 * Gives you a begin() iterator to iterate over all active windows.
	 */
	static SlotMap<Window>::Iterator begin();

	/**
	 * Gives you a end() iterator to iterate over all active windows.
	 */
	static SlotMap<Window>::Iterator end();
};
