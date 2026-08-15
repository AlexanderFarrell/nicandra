#pragma once

#include <any>
#include <cstddef>
#include <functional>
#include <memory>
#include <optional>
#include <typeindex>
#include <utility>
#include <vector>

/**
* Allows you to add, get and remove items based on their type. Holds up to one
* of each type.
*
* Very helpful for adding data and behavior to an object flexibly, such as a
* character in a video game. Maybe character A can move, is visible, and can
* shoot. Whereas character B can move, and is visible. And yet character C
* is visible and can shoot. Instead of a strange subclass spiderweb, you can
* make components for these like VisibleObj, Combat, and Movement, then add
* them to applicable objects.
*
* This TypeMap is optimized for holding less than ~16 components at a time
* and uses vector storage internally to reduce heap allocations. Though you
* absolutely can have more components if you like. This is generally appropriate
* for a game where you have lots of NPCs and objects with a few components each.
*/
class TypeMap {
private:
	/**
	* The internal storage of objects. Vector storage is used to reduce heap allocations,
	* as generally speaking, not many will be allocated at a time.
	*/
	std::vector<std::pair<std::type_index, std::shared_ptr<std::any>>> objects;
public:
	TypeMap() = default;
	virtual ~TypeMap() = default;

	/**
	* Adds the item if it doesn't exist, or replaces the item if it does. To
	* prevent unwanted replacement, call `has()` to determine if we already have
	* an object of that type.
	*/
	template <class T> void set_item(T item) {
		// If we already have it, then replace. Users should use has() if they don't want replaced.
		for (std::size_t i = 0; i < this->objects.size(); i++) {
			auto &pair = this->objects[i];
			auto type_index = std::type_index(typeid(T));
			if (pair.first == type_index) {
				pair.second = std::move(item);
				return;
			}
		}

		// If we didn't find it, add a new one
		this->objects.push_back(std::make_pair(std::type_index(typeid(T)), std::move(item)));
	}

	/**
	* Gets a reference to an item of the specified type, if we have it. 
	*/
	template <class T> std::optional<std::weak_ptr<T>> get_item() {
		// Look for it
		auto type_index = std::type_index(typeid(T));
		for (auto &pair : this->objects) {
			if (pair.first == type_index) {
				return std::make_optional(std::ref(pair.second));
			}
		}
		// We didn't find it.
		return std::nullopt;
	}

	/**
	* Returns true if an item of the given type exists, false otherwise.
	*/
	template <class T> bool has_item() {
		auto type_index = std::type_index(typeid(T));
		for (auto &pair : this->objects) {
			if (pair.first == type_index) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Removes the given item if it exists. Returns true if successful
	 * false otherwise.
	 */
	template <class T> bool remove_item() {
		auto type_index = std::type_index(typeid(T));
		for (std::size_t i = 0; i < this->objects.size(); i++) {
			if (this->objects[i].first == type_index) {
				this->objects.erase(this->objects.begin() + i);
				return true;
			}
		}
		return false;
	}

	/**
	* Removes all items from the collection. 
	*/
	void clear();

	/**
	 * Removes all items from the collection. Alias for `clear()`
	 */
	void remove_all();

	/**
	* Returns the number of items in the collection. 
	*/
	std::size_t size();

	/**
	 * Returns the number of items in the collection. Alias for `size()`
	 */
	std::size_t count();

	/**
	* Returns true if the collection has 0 items, false if it has 1 or more.
	*/
	bool is_empty();
};