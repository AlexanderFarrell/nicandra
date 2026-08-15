#pragma once

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "stage.hpp"

// Lifetime of the entire application.

// TODO: Might get rid of this namespace, might be more annoying than anything.
namespace Nicandra {

/**
* Runs a Nicandra instance, with windows, graphics, input, etc. Defines what
* should happen at start up and closing.
*/
class App {
private:
	/**
	* Major states of the app. In a game, we might have: Menu, Gameplay,
	* Editor, LoadingScreen, etc.
	*/
	std::unordered_map<std::string, Stage> stages;

	/**
	* A copy of the current stage being used.
	*/
	std::optional<Stage> current;
public:
	/**
	* Creates a new Nicandra App/Game with stages.
	*/
	App(const std::vector<Stage> stages);

	~App() = default;

	/**
	* Adds a new stage. You can then switch to it with `switch_stage()`
	*/
	void add_stage(const Stage &stage);

	/**
	* Runs the game or app. Consumes the thread. Must be run by the main thread.
	*/
	void run(const std::string &start_stage_name);

	/**
	* Switches to the given stage. Use this to switch to the Menu, Editor,
	* Gameplay, etc.
	*/
    void switch_stage(const std::string &next_stage_name);
};

/**
* Helper function to run Nicandra with a single function to call when it starts
* (for setup). Call this from the main thread. Consumes the thread.
*/
void run_basic(std::function<void()> on_start);

/**
* Helper function to run Nicandra with a function to call on start and end
* of running the app. Call this from the main thread. Consumes the thread.
*/
void run_basic(std::function<void()> on_start, std::function<void()> on_end);

}