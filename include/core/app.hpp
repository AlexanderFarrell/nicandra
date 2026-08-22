#pragma once

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "stage.hpp"
#include "config.hpp"

// Lifetime of the entire application.

// TODO: Might get rid of this namespace, might be more annoying than anything.
namespace nc {

enum AppRuntimeType {
    ARTRealtime,
    ARTEvent,
    ARTServer,
    ARTSingle,
};

struct AppInfo {
    Config config;
    std::string app_name;
    Version app_version;
    AppRuntimeType runtime_type = AppRuntimeType::ARTRealtime;

    std::function<void()> on_start;
    std::function<void()> on_end;
};

/**
* Runs a Nicandra instance, with windows, graphics, input, etc. Defines what
* should happen at start up and closing.
*/
class App {
private:
    static AppInfo info;
    static bool running;
public:
	/**
	* Runs the game or app. Consumes the thread. Must be run by the main thread.
	*/
	static void run(const AppInfo& info);
    static void stop();
    static void panic(const std::string& message);

    static bool is_running();
};

}
