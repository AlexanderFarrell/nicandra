#include "util/data/typemap.hpp"
#include <cstddef>

void TypeMap::remove_all() {
	this->clear();
}

void TypeMap::clear() {
	this->objects.clear();
}

std::size_t TypeMap::count() { return this->size(); }

std::size_t TypeMap::size() { return this->objects.size(); }

bool TypeMap::is_empty() {
	return this->objects.empty();
}