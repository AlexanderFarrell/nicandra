#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "../util/data/slotmap.hpp"
#include "../util/data/flatmap.hpp"
#include "spdlog/spdlog.h"
#include <utility>
#include <vector>

class Component;
class Universe;
class World;
class Entity;

// class Entity {
// private:
// 	TypeMap _components;
// 	bool _is_active;
// public:
// 	template <class T> std::optional<std::reference_wrapper<T>> get() {
// 		static_assert(std::is_base_of<Component, T>::value,
// 		              "You can only retrieve an object of subclass Component "
// 		              "from an Entity");
// 		return this->_components.get_item<T>();
// 	}

// 	template <class T> void set(T component) {
// 		static_assert(
// 		    std::is_base_of<Component, T>::value,
// 		    "You can only add objects of type Component to the Entity");

// 		this->call_on_end<T>();
// 		this->_components.set_item(component);
// 		this->call_on_start<T>();
// 	}

// 	template <class T> bool has() {
// 		static_assert(std::is_base_of<Component, T>::value,
// 		              "Any object which is not a base class of Component will "
// 		              "not be contained");
// 		return this->_components.has_item<T>();
// 	}

// 	template <class T> bool remove() {
// 		static_assert(std::is_base_of<Component, T>::value,
// 					"Any object which is not a base class of Component will "
// 					"not be contained");

// 		this->call_on_end<T>();
// 		return this->_components.remove_item<T>();
// 	}

// 	// void clear() {
// 	// 	if (this->_is_active) {
// 	// 		for (auto &c : this->_components) {
				
// 	// 		}
// 	// 	}
// 	// }

// private:
// 	template <class T> void call_on_start() {
// 		if (this->_is_active) {
// 			std::optional<std::weak_ptr<T>> weak_ptr_component = this->get<T>();
// 			if (weak_ptr_component.has_value()) {
// 				if (std::shared_ptr<T> spt =
// 				        weak_ptr_component.value().lock()) {
// 					spt.get().on_start();
// 				} else {
// 					spdlog::error("Component could not be locked");
// 				}
// 			}
// 		}
// 	}

// 	template <class T> void call_on_end() {
// 		if (this->_is_active) {
// 			std::optional<std::weak_ptr<T>> weak_ptr_component = this->get<T>();
// 			if (weak_ptr_component.has_value()) {
// 				if (std::shared_ptr<T> spt =
// 				        weak_ptr_component.value().lock()) {
// 					spt.get().on_end();
// 				} else {
// 					spdlog::error("Component could not be locked");
// 				}
// 			}
// 		}
// 	}
// };

class ComponentStorage {
private:
	std::unordered_map<std::type_index, std::unique_ptr<ISlotMap>> components;

public:
	template <class T> 
	GenIndex add(T t) {
		auto type_index = std::type_index(typeid(T));
		// Lazy add a slot map if it doesn't exist
		if (!components.contains(type_index)) {
			components.insert(
				type_index,
				std::make_unique<SlotMap<T>>()
			);
		}

		// Add the component
		SlotMap<T>& map = *this->components.at(type_index);
		auto index = map.add(std::move(t));
		return index;
	}

	template <class T>
	std::optional<std::reference_wrapper<T>> get(const GenIndex& index) {
		auto type_index = std::type_index(typeid(T));

		SlotMap<T>& map = *this->components.at(type_index);
		return map.get(index);
	}

	template <class T>
	void remove(const GenIndex& index) {
		auto type_index = std::type_index(typeid(T));
		SlotMap<T>& map = *this->components.at(type_index);
		map.remove(index);
	}

	template <class T>
	std::vector<std::reference_wrapper<T>> get_all_of_type() {
		auto type_index = std::type_index(typeid(T));
		SlotMap<T>& map = *this->components.at(type_index);
		std::vector<std::reference_wrapper<T>> ret_val;
		for (auto &component : map) {
			ret_val.push_back(std::ref(component));
		}
		return ret_val;
	}

	// template <class T>
	// void set(T t) {
	// 	auto type_index = std::type_index(typeid(T));
	// 	if (!components.contains(type_index)) {
	// 		this->add(t);
	// 	}
	// 	SlotMap<T>& map = *this->components.at(type_index);
	// 	auto index = map.
	// }
};

class World {
private:
	SlotMap<Entity> entities;

public:
	ComponentStorage components;
};


class Universe {
public:
	static SlotMap<World> worlds;

	template <class T>
	std::vector<std::reference_wrapper<T>> get_components_of_type() {
		std::vector<std::reference_wrapper<T>> ret_val;
		for (auto &world : this->worlds) {
			auto& components = world.components.get_all_of_type<T>();
			ret_val.insert(ret_val.end(), components.begin(), components.end());
		}
		return ret_val;
	}
};

class Entity{
private:
	GenIndex world_index;
	FlatMap<std::type_index, GenIndex> _components;
	bool is_active;
	virtual ~Entity() = default;
public:
	template <class T>
	std::optional<std::reference_wrapper<T>> get() {
		auto type_index = std::type_index(typeid(T));
		auto index = this->_components.get(type_index);
		if (index.has_value()) {
			auto& world = Universe::worlds.get(world_index)->get();
			return world.components.get<T>(index.value());
		}
		return std::nullopt;
	}

	template <class T>
	void remove() {
		auto type_index = std::type_index(typeid(T));
		auto index = this->_components.get(type_index);
		if (index.has_value()) {
			auto& world = Universe::worlds.get(world_index)->get();
			world.components.remove<T>(index);
			this->_components.remove(type_index);
		}
	}

	template <class T>
	bool has() {
		auto type_index = std::type_index(typeid(T));
		return this->_components.has(type_index);
	} 

	template <class T>
	void add(T t) {
		auto type_index = std::type_index(typeid(T));
		auto& world = Universe::worlds.get(world_index)->get();
		auto index = world.components.add(t);
		this->_components.set(type_index, index);
	}
};




class Component {
private:
	GenIndex entity_id;
	bool active;
protected:
	virtual void on_start() = 0;
	virtual void on_end() = 0;
	bool is_active();

	friend class Entity;
};