#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <vector>
#include "../util/data/slotmap.hpp"

class World {};

class Component;

class Entity {
private:
	std::vector<std::pair<std::type_index, std::unique_ptr<Component>>> _components;
public:
	template <class T> std::optional<std::reference_wrapper<T>> get() {
		static_assert(std::is_base_of<Component, T>::value,
		              "You can only retrieve an object of subclass Component "
		              "from an Entity");
		for (auto& component : this->_components) {
			if (component.first == std::type_index(typeid(T))) {
				return std::make_optional(std::ref(component.second));
			}
		}
		return std::nullopt;
	}

	template <class T> void set(T component) {
		static_assert(
		    std::is_base_of<Component, T>::value,
		    "You can only add objects of type Component to the Entity");
		
	}

	
};


class Component {
private:
	GenIndex entity_id;
protected:
	virtual void on_start() = 0;
	virtual void on_end() = 0;

	friend class Entity;
};