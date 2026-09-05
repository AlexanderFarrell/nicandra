#pragma once

#include "gpu/texture.hpp"

class OpenGLTexture: public GPUTexture {
	void buffer(const Texture &texture) override;
};