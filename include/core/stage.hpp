#pragma once

#include <string>
#include <functional>

/**
* Represents a state of the game, like Gameplay, Menu, Editor,
* LoadingScreen, etc. Makes it easy to switch between these.
*/
struct Stage {
	/**
	* What is the name of this? You could put "menu", "editor",
	* "loading_screen", etc. Use this to call App::switch_stage().
	*/
	std::string name;

	/**
	* Used to set up the stage. For a menu, you might create the buttons,
	* and UI here for example.
	*/
	std::function<void()> on_start;

	/**
	* Used to do any breakdown, if needed. Or if you want something called
	* when the stage ends, such as saving the game. 
	*/
	std::function<void()> on_end;
};