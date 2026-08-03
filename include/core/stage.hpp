#pragma once

#include <string>
#include <functional>

struct Stage {
	std::string name;
	std::function<void()> on_start;
	std::function<void()> on_end;
};