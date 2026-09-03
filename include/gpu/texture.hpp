#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "assets/types.hpp"

class Texture {
public:
	uint16_t width;
	uint16_t height;
	std::vector<uint8_t> data;
	GenIndex gpu_texture;

private:
	uint8_t flags;
	Texture(uint16_t width, uint16_t height, uint8_t flags);
	Texture(const std::string& filename);
	Texture(const glm::vec3& color);

public:
	virtual ~Texture();
	static AssetID create(uint16_t width, uint16_t height, uint8_t flags);
	static AssetID load(const std::string& filename);
	static AssetID create_from_color(const glm::vec3& color);
	void buffer();
};

class GPUTexture {
	virtual void buffer(const Texture& texture) = 0;
};
