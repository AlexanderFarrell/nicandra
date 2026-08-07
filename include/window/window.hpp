#pragma once

#include <cstddef>
#include "../util/data/slotmap.hpp"

class Window {

};


class WindowManager {
private:
	static SlotMap<Window> _windows;
public:
	Window &main_window();
	Window &get_by_id(std::size_t index);
	Window &get_by_id(GenIndex& index);
	Window &spawn();
	Window &remove(std::size_t index);
	Window &remove(GenIndex &index);

	SlotMap<Window>::Iterator begin();
	SlotMap<Window>::Iterator end();
};