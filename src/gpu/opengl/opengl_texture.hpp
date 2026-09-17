#pragma once

#include "gl.hpp"
#include "gpu/texture.hpp"

class OpenGLTexture : public GPUTexture {
private:
	GLuint texture_binding = 0;
public:
	void buffer(const Texture &texture) override;
	void use(int texture_number = 0) override;
	void destroy() override;
};
