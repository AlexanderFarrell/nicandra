#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <type_traits>

#include "../util/data/slotmap.hpp"
#include "../util/data/typemap.hpp"
#include "spdlog/spdlog.h"

class World {};

class Component;

class Entity {
private:
	TypeMap _components;
	bool _is_active;
public:
	template <class T> std::optional<std::reference_wrapper<T>> get() {
		static_assert(std::is_base_of<Component, T>::value,
		              "You can only retrieve an object of subclass Component "
		              "from an Entity");
		return this->_components.get_item<T>();
	}

	template <class T> void set(T component) {
		static_assert(
		    std::is_base_of<Component, T>::value,
		    "You can only add objects of type Component to the Entity");

		this->call_on_end<T>();
		this->_components.set_item(component);
		this->call_on_start<T>();
	}

	template <class T> bool has() {
		static_assert(std::is_base_of<Component, T>::value,
		              "Any object which is not a base class of Component will "
		              "not be contained");
		return this->_components.has_item<T>();
	}

	template <class T> bool remove() {
		static_assert(std::is_base_of<Component, T>::value,
					"Any object which is not a base class of Component will "
					"not be contained");

		this->call_on_end<T>();
		return this->_components.remove_item<T>();
	}

	void clear() {
		if (this->_is_active) {
			for (auto c : this->_components) {
				
			}
		}
	}

private:
	template <class T> void call_on_start() {
		if (this->_is_active) {
			std::optional<std::weak_ptr<T>> weak_ptr_component = this->get<T>();
			if (weak_ptr_component.has_value()) {
				if (std::shared_ptr<T> spt =
				        weak_ptr_component.value().lock()) {
					spt.get().on_start();
				} else {
					spdlog::error("Component could not be locked");
				}
			}
		}
	}

	template <class T> void call_on_end() {
		if (this->_is_active) {
			std::optional<std::weak_ptr<T>> weak_ptr_component = this->get<T>();
			if (weak_ptr_component.has_value()) {
				if (std::shared_ptr<T> spt =
				        weak_ptr_component.value().lock()) {
					spt.get().on_end();
				} else {
					spdlog::error("Component could not be locked");
				}
			}
		}
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