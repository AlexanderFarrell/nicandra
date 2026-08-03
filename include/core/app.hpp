#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include "stage.hpp"
#include "util/result.hpp"

namespace Nicandra {

class App {
private:
	std::unordered_map<std::string, Stage> stages;
public:
	App(const std::vector<Stage> stages);
	~App() = default;
	void add_stage(const Stage& stage);
	void run();
};

void run_basic(std::function<void()> on_start, std::function<void()> on_end);

}