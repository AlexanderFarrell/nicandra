#include "core/app.hpp"
#include <chrono>
#include <csignal>
#include <functional>
#include <optional>
#include <string>
#include <thread>
#include <vector>
#include "core/engine.hpp"
#include "spdlog/spdlog.h"
#include "window/window.hpp"

std::optional<std::function<void()>> on_signal;
void handle_int_signal(int signal) {
  switch (signal) {
  case SIGINT:
    if (on_signal.has_value()) {
      // Shutdown gracefully
      on_signal.value()();
    } else {
      exit(signal);
	}
    break;
  default:
    spdlog::error("Unhandled signal");
    exit(signal);
  }
}

Nicandra::App::App(const std::vector<Stage> stages) {
	for (auto &stage : stages) {
		this->add_stage(stage);
	}
}

void Nicandra::App::add_stage(const Stage& stage) {
	this->stages[stage.name] = stage;
}

void Nicandra::App::run(const std::string& start_stage_name) {
  if (this->stages.empty()) {
		spdlog::error("Please add at least one stage before calling run");
        return;
  }

  on_signal = []() {
	Engine::running = false;
  };
  signal(SIGINT, handle_int_signal);

  // Initialize
  WindowManager::setup();

  Engine::running = true;

  this->switch_stage(start_stage_name);

  while (Engine::running) {
	  WindowManager::update();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  this->switch_stage("");

  WindowManager::breakdown();

  Engine::running = false;
}

void Nicandra::App::switch_stage(const std::string &stage_name) {
	if (this->current.has_value()) {
		this->current->on_end();
		spdlog::debug("Ended stage " + this->current->name);
	}

	this->current = (this->stages.contains(stage_name))
                    ? std::make_optional(this->stages[stage_name])
                    : std::nullopt;

	if (this->current.has_value()) {
		spdlog::debug("Switched to stage " + this->current->name);
		this->current->on_start();
	}	
}

void Nicandra::run_basic(std::function<void()> on_start) {
  Nicandra::run_basic(on_start, []() {});
}

void Nicandra::run_basic(std::function<void()> on_start, std::function<void()> on_end) {
  Nicandra::App app({Stage{
      .name = "main",
      .on_start = on_start,
      .on_end = on_end,
  }});
  
  app.run("main");
}