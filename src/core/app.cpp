#include "core/app.hpp"
#include <functional>
#include <vector>

Nicandra::App::App(const std::vector<Stage> stages) {
	for (auto &stage : stages) {
		this->add_stage(stage);
	}
}

void Nicandra::App::add_stage(const Stage& stage) {
	this->stages[stage.name] = stage;
}

void Nicandra::App::run() {
	if (this->stages.empty()) {
        return;
    }
}

void Nicandra::run_basic(std::function<void()> on_start, std::function<void()> on_end) {
  Nicandra::App app({Stage{
      .name = "main",
      .on_start = on_start,
      .on_end = on_end,
  }});
  
  app.run();
}