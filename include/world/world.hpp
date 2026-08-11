#pragma once

#include <memory>
#include <vector>
#include "../util/data/slotmap.hpp"

class World {};

class Component;

class Entity {
private:
	std::vector<std::unique_ptr<Component>> _components;
public:
	
};


class Component {
private:
	GenIndex entity_id;
protected:
	virtual void on_start() = 0;
	virtual void on_end() = 0;

	friend class Entity;
};