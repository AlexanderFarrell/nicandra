#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <typeindex>
#include <utility>
#include <vector>

template <class TKey, class TValue>
class FlatMap {
private:
	std::vector<std::pair<TKey, TValue>> key_values;

public:
	std::optional<std::reference_wrapper<TValue>> get(const TKey& key) {
		for (auto &pair : this->key_values) {
			if (pair.first == key) {
				return std::ref(pair.second);
			}
		}
		return std::nullopt;
	}

	void set(const TKey& key, TValue& value) {
		for (auto &pair : this->key_values) {
			if (pair.first == key) {
				pair.second = std::move(value);
			}
		}

		this->key_values.push_back(std::make_pair(
			std::type_index(typeid(TKey)), 
			std::move(value)));
	}

	bool has(const TKey& key) {
		for (auto &pair : this->key_values) {
			if (pair.first == key) {
				return true;
			}
		}
		return false;
	}

	void remove(const TKey& key) {
		for (std::size_t i = 0; i < this->key_values.size(); i++) {
			if (this->key_values[i].first == key) {
				this->key_values.erase(this->key_values.begin() + i);
				return;
			}
		}
	}
};