#include "core/app.hpp"
#include "spdlog/spdlog.h"

#include <chrono>
#include <string>
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

