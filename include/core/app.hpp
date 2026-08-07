#pragma once

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "stage.hpp"

namespace Nicandra {

class App {
private:
  std::unordered_map<std::string, Stage> stages;
  std::optional<Stage> current;
public:
	App(const std::vector<Stage> stages);
	~App() = default;
	void add_stage(const Stage& stage);
    void run(const std::string &start_stage_name);
    void switch_stage(const std::string &next_stage_name);
};

void run_basic(std::function<void ()> on_start);
void run_basic(std::function<void()> on_start, std::function<void()> on_end);

}