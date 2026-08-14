#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <vector>
#include <cstdint>
#include <iterator>

struct GenIndex {
	std::size_t index = 0;
	std::uint32_t generation = 0;
};

template <class T> class SlotMap {
private:
	struct Slot {
		std::optional<T> data = std::nullopt;
		std::uint32_t generation = 0;
		std::size_t iter_index = 0;
	};

	std::vector<Slot> _slots;
	std::vector<std::size_t> _freelist;
	std::vector<std::size_t> _iter_vector;
public:
	SlotMap() = default;
	SlotMap(std::size_t capacity) : _slots(capacity), _iter_vector(capacity) {};
	virtual ~SlotMap() = default;

	// Add, remove, get, set operations
	GenIndex add(T item) {
		if (!this->_freelist.empty()) {
			// Get an empty slot
			std::size_t index = this->_freelist[this->_freelist.size()-1];
			this->_freelist.pop_back();
			Slot &slot = this->_slots[index];
			slot.data.emplace(std::move(item));
			slot.generation++;
			this->_iter_vector.push_back(index);
			slot.iter_index = this->_iter_vector.size() - 1;
			return GenIndex {
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
			this->_iter_vector.push_back(index);
			this->_slots[index].iter_index = this->_iter_vector.size()-1;
			return GenIndex {
				.index = index,
				.generation = 0,
			};
		}
	}

	void remove(const std::size_t index) {
		Slot &slot = this->_slots[index];
		slot.data = std::nullopt;

		// Remove from iter index, swapping with last one for wonderful O(1)
		if (this->_iter_vector.size() > 1) {
			this->_iter_vector[slot.iter_index] = this->_iter_vector[this->_iter_vector.size() - 1];
		}
		this->_iter_vector.pop_back();

		// Add to freelist
		this->_freelist.push_back(index);
	}

	void remove(const GenIndex &index) {
		Slot &slot = this->_slots[index.index];
		if (slot.generation == index.generation) {
			this->remove(index.index);
		}
	}

	std::optional<std::reference_wrapper<T>> get(const std::size_t index) {
		return std::ref(*this->_slots[index].data);
	}

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

	void clear() {
		// No need to hold any empty slots.
		this->_slots.clear();
		this->_iter_vector.clear();
		this->_freelist.clear();
	}

	// Meta operations
	std::size_t size_active() { return this->_slots.size() - _freelist.size(); }

	class Iterator {
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T *;
		using reference = T &;
		using VectorIterator = std::vector<std::size_t>::iterator;

		Iterator() = default;
		Iterator(SlotMap<T>* map, VectorIterator iv_ptr)
		    : _map(map), _iv_ptr(iv_ptr) {}
	private:
		SlotMap* _map;
		VectorIterator _iv_ptr;
	public:
		reference operator*() const {
			Slot& slot = _map->_slots[*_iv_ptr];
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

	Iterator begin() {
		return Iterator(this, this->_iter_vector.begin());
	}

	Iterator end() {
		return Iterator(this, this->_iter_vector.end());
	}
};
