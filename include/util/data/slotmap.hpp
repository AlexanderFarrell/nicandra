#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <iterator>
#include <limits>
#include <optional>
#include <vector>

/**
 * A weak, safe reference to an object within a SlotMap.
 */
struct GenIndex {
	/**
	 * Represents the slot position within a SlotMap, empty or occupied.
	 */
	std::size_t index = 0;

	/**
	 * Ensures if the referenced object is removed, and something else takes
	 * it's slot, that we don't reference the new (and thus wrong) object.
	 *
	 * Every slot holds which "generation" it is, if an object is removed from
	 * a slot, then another added, the "generation" for that slot is incremented
	 * by one.
	 *
	 * This allows us to recycle memory, while also ensuring we don't reference
	 * the wrong object.
	 */
	std::uint32_t generation = std::numeric_limits<uint32_t>::max();
};

class ISlotMap {
public:
	virtual ~ISlotMap() = default;
};


/**
 * A linear data store with the following perks:
 *   1. Reduces memory fragmentation
 *   2. Holds steady, unchanging indices of elements
 *      (no need for pointers, but you can still use if you like)
 *   3. O(1) complexity for add, remove, get and set.
 *
 * This data structure functions similar to a parking lot
 * with spots either occupied or empty. It has some optimizations
 * too for finding spots, and faster iteration.
 */
template <class T> class SlotMap : public ISlotMap {
private:
	/**
	 * Holds a spot for an object which may be occupied or empty.
	 */
	struct Slot {
		/**
		 * The spot for the object, either occupied or empty.
		 */
		std::optional<T> data = std::nullopt;

		/**
		 * Increments every time this spot is occupied by
		 * a new object. Ensures that objects referencing a
		 * previously occupying object do not now reference
		 * the new (and thus incorrect) object.
		 */
		std::uint32_t generation = 0;

		/**
		 * Where the object is located in the _iter_vector
		 * (only applicable if the slot is occupied)
		 */
		std::size_t iter_index = 0;
	};

	/**
	 * Each slot in linear fashion.
	 */
	std::vector<Slot> _slots;

	/**
	 * A helper vector of empty slots. If we need to add
	 * a new object, this greatly speeds up searching for
	 * an empty spot!
	 */
	std::vector<std::size_t> _freelist;

	/**
	 * A helper vector containing an index to all occupied slots.
	 * Not guaranteed to be in order in return for further optimization.
	 *
	 * Speeds up iteration, as we don't have to check if each spot
	 * is empty.
	 */
	std::vector<std::size_t> _iter_vector;
public:
	/**
	 * Creates a new slot map.
	 */
	SlotMap() = default;

	/**
	 * Creates a new slot map with the given vector capacity. If you know you
	 * will use at least this much capacity, its a useful optimization, but
	 * completely optional.
	 */
	SlotMap(std::size_t capacity) : _slots(capacity), _iter_vector(capacity) {};

	~SlotMap() = default;

	// Add, remove, get, set operations

	/**
	 * Places the item inside the SlotMap, returning its location.
	 *
	 * This internally will either:
	 *   1. Place the item in an empty slot if one exists.
	 *   2. Grow the SlotMap to make room.
	 */
	GenIndex add(T item) {
		// Check if we have empty slots.
		if (!this->_freelist.empty()) {
			// Get an empty slot from our freelist.
			std::size_t index = this->_freelist[this->_freelist.size() - 1];
			this->_freelist.pop_back();

			// Move the item into the slot.
			Slot &slot = this->_slots[index];
			slot.data.emplace(std::move(item));

			// Add to its generation so old references do not get this new
			// object.
			slot.generation++;

			// Add to iter vector, for fast iteration later.
			this->_iter_vector.push_back(index);
			slot.iter_index = this->_iter_vector.size() - 1;
			return GenIndex{
			    .index = index,
			    .generation = slot.generation,
			};
		} else {
			// Make a new slot
			this->_slots.push_back(Slot{
			    .data = std::move(item),
			    .generation = 0,
			});
			std::size_t index = _slots.size() - 1;

			// Add to the iter vector for fast iteration later.
			this->_iter_vector.push_back(index);
			this->_slots[index].iter_index = this->_iter_vector.size() - 1;
			return GenIndex{
			    .index = index,
			    .generation = 0,
			};
		}
	}

	/**
	 * Removes the item at the slot. A safer approach is to pass a GenIndex
	 * instead. O(1)
	 */
	void remove(const std::size_t index) {
		// Just set the slot to empty!
		Slot &slot = this->_slots[index];
		slot.data = std::nullopt;

		// Remove from iter index, swapping with last one for wonderful O(1)
		if (this->_iter_vector.size() > 1) {
			this->_iter_vector[slot.iter_index] =
			    this->_iter_vector[this->_iter_vector.size() - 1];
		}
		this->_iter_vector.pop_back();

		// Add to freelist
		this->_freelist.push_back(index);
	}

	/**
	 * Safely removes the item only if it references the same one
	 * currently at the slot. O(1)
	 */
	void remove(const GenIndex &index) {
		Slot &slot = this->_slots[index.index];
		if (slot.generation == index.generation) {
			this->remove(index.index);
		}
	}

	/**
	 * Gets the item at the given slot. It's possible the item was removed
	 * and another item took the slot. It's safer to pass a GenIndex if you
	 * need to guarantee you get the same item back.
	 *
	 * Returns the item if slot occupied, or std::nullopt if empty.
	 */
	std::optional<std::reference_wrapper<T>> get(const std::size_t index) {
		return std::ref(*this->_slots[index].data);
	}

	/**
	 * Safely gets the exact item at the given slot, if it exists.
	 */
	std::optional<std::reference_wrapper<T>> get(const GenIndex &index) {
		// Gen index also benefits from checking for size
		if (index.index >= this->_slots.size()) {
			return std::nullopt;
		}

		Slot &slot = this->_slots[index.index];
		if (slot.generation == index.generation) {
			return std::ref(*this->_slots[index.index].data);
		} else {
			return std::nullopt;
		}
	}

	// std::size_t set(T item, std::size_t index) {
	// 	// The slot might be empty, if this is the case we are adding.

	// }

	/**
	 * Empties all slots.
	 */
	void clear() {
		// No need to hold any empty slots.
		this->_slots.clear();
		this->_iter_vector.clear();
		this->_freelist.clear();
	}

	// Meta operations

	/**
	 * Returns the number of occupied slots.
	 */
	std::size_t size_active() { return this->_slots.size() - _freelist.size(); }

	/**
	 * Holds a spot while iterating through the SlotMap.
	 */
	class Iterator {
	public:
		// Since the order doesn't matter, bidirectional is slightly
		// disingenuous, but you can still loop backwards if you want.
		// This is mostly if you want to step backwards for some reason.
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T *;
		using reference = T &;
		using VectorIterator = std::vector<std::size_t>::iterator;

		Iterator() = default;
		Iterator(SlotMap<T> *map, VectorIterator iv_ptr)
		    : _map(map), _iv_ptr(iv_ptr) {}
	private:
		/**
		 * The current map we are iterating through.
		 */
		SlotMap *_map;

		/**
		 * The iterator to the internal iter_vector vector.
		 */
		VectorIterator _iv_ptr;
	public:
		reference operator*() const {
			Slot &slot = _map->_slots[*_iv_ptr];
			return slot.data.value();
		}

		pointer operator->() {
			Slot &slot = _map->_slots[*_iv_ptr];
			return &slot.data.value();
		}

		Iterator &operator++() {
			_iv_ptr++;
			return *this;
		}

		Iterator &operator--() {
			_iv_ptr--;
			return *this;
		}

		friend bool operator==(const Iterator &a, const Iterator &b) {
			// Honestly, the pointer is within the _map anyway, so just
			// compare the _iv_ptr
			return a._iv_ptr == b._iv_ptr;
		}

		friend bool operator!=(const Iterator &a, const Iterator &b) {
			return a._iv_ptr != b._iv_ptr;
		}
	};

	/**
	 * Gets an iterator at the beginning.
	 */
	Iterator begin() { return Iterator(this, this->_iter_vector.begin()); }

	/**
	 * Gets an iterator at the end.
	 */
	Iterator end() { return Iterator(this, this->_iter_vector.end()); }
};
