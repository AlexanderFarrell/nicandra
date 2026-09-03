#include "gpu/texture.hpp"
#include "assets/assets.hpp"

Texture::Texture(uint16_t width, uint16_t height, uint8_t flags) {
	this->width = width;
	this->height = height;
	this->flags = flags;
}

Texture::Texture(const glm::vec3 &color) {

}

Texture::Texture(const std::string &filename) {

}

AssetID Texture::create(uint16_t width, uint16_t height, uint8_t flags) {
	throw std::runtime_error("Not implemented");
}

AssetID Texture::load(const std::string &filename) {
	throw std::runtime_error("Not implemented");
}

AssetID Texture::create_from_color(const glm::vec3 &color) {
	throw std::runtime_error("Not implemented");
}