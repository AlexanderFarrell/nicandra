#include "core/app.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <nicandra.hpp>

void start() {
  spdlog::info("Hello from Test Window");
}

void end() {
	spdlog::info("Goodbye from Test Window");
}

int main() {
	spdlog::set_level(spdlog::level::debug);
  Nicandra::run_basic(start, end);
}