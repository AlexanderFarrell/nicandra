#include <chrono>
#include <optional>
#include <string>
#include "core/app.hpp"
#include "core/config.hpp"
#include "spdlog/spdlog.h"
#include <csignal>
#include <cstdlib>
#include <thread>


AppInfo App::info;
bool App::running;

void handle_int_signal(int signal) {
  switch (signal) {
    case SIGINT:
      App::stop();
      break;
    default:
      App::panic("Unhandled signal: " + std::to_string(signal));
  }
}

void App::run(const AppInfo &info) {
  signal(SIGINT, handle_int_signal);

  App::running = true;

  spdlog::debug("Running " + info.app_name);
  while (App::running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
  }
}

void App::stop() {
  // Sets to false to gracefully shutdown next game loop.
  App::running = false;
}

void App::panic(const std::string& message) {
  spdlog::error(message);
  std::abort();
}

bool App::is_running() {
    return App::running;
}


/*
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
	// Temporary, do config
	Config config = {
		.window = {
		 .title = "Hello",
		 .width = 1279,
		 .height = 719,
		},
    .gpu = {
      .graphics_api = GraphicsAPIKind::GApiOpenGL,
      .compute_api = ComputeAPIKind::CApiOpenCL,
    }
	};


  if (this->stages.empty()) {
		spdlog::error("Please add at least one stage before calling run");
        return;
  }

  on_signal = []() {
	Engine::running = false;
  };
  signal(SIGINT, handle_int_signal);

  // Initialize
  GPU::setup_engine(config);
  Window::setup_engine(config);

  Engine::running = true;

  this->switch_stage(start_stage_name);

  while (Engine::running) {
	Window::update_engine();
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
  }

  this->switch_stage("");

  Window::breakdown_engine();
  GPU::breakdown_engine();

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
*/
