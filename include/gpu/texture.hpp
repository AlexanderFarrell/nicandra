#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "assets/types.hpp"

enum TextureFilter {
	TFNearestNeighbor,
	TFBilinear,
	TFBilinearMipMapped,
	TFTrilinear,
	TFAnisotropic2,
	TFAnisotropic4,
	TFAnisotropic8,
	TFAnisotropic16,
};

class Texture {
public:
	uint16_t width;
	uint16_t height;
	std::vector<uint8_t> data;
	GenIndex gpu_texture;

private:
	Texture(uint16_t width, uint16_t height);
	Texture(const std::string &filename);
	Texture(const glm::vec3 &color);

public:
	TextureFilter filter = TFTrilinear;
	bool has_alpha = true;

	virtual ~Texture();
	static AssetID create(uint16_t width, uint16_t height);
	static AssetID load(const std::string &filename);
	static AssetID create_from_color(const glm::vec3 &color);
	void buffer();
	bool has_mipmap();
};

class GPUTexture {
	virtual void buffer(const Texture &texture) = 0;
	virtual void use(int texture_number = 0) = 0;
	virtual void destroy() = 0;
};
