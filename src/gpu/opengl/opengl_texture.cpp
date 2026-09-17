#include "opengl_texture.hpp"
#include "core/app.hpp"
#include "gl.hpp"
#include "gpu/texture.hpp"
#include <OpenGL/gl3ext.h>

void OpenGLTexture::buffer(const Texture &texture) {
	this->destroy();
	glGenTextures(1, &this->texture_binding);
	glBindBuffer(GL_TEXTURE_2D, this->texture_binding);
	glTexBuffer(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexBuffer(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	check_for_errors_gl();

	// How should the texture be drawn when the area is smaller than the
	// texture? Or how do we shrink the texture? Normally we use mipmapping, or
	// anisotropic
	GLenum minification_filter = GL_NEAREST;

	// How should the texture be drawn when the area is larger than the texture?
	// Or how do we make the texture bigger? Interpolate? Pick the nearest
	// neighbor?
	GLenum magnification_filter = GL_NEAREST;

	// What if the width is larger than height? Or height larger than width?
	// Can we sample the texture more in the larger direction? Requires more
	// power, but gets sharper textures, especially at an angle, if this
	// number is higher.
	//
	// Anisotrophy means "not equal directions", An- (not), Iso- (equal),
	// Trop- (direction or way).
	GLfloat max_anisotropy = 1.0f;

	// Gets the max anisotrophic texture sampling supported by the device.
	GLfloat max_anisotropy_supported = 1.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy_supported);

	switch (texture.filter) {
	case TextureFilter::TFNearestNeighbor:
		minification_filter = GL_NEAREST;
		magnification_filter = GL_NEAREST;
		break;
	case TextureFilter::TFBilinear:
		minification_filter = GL_LINEAR;
		magnification_filter = GL_LINEAR;
		break;
	case TextureFilter::TFBilinearMipMapped:
		minification_filter = GL_LINEAR_MIPMAP_NEAREST;
		magnification_filter = GL_LINEAR;
		break;
	case TextureFilter::TFTrilinear:
		minification_filter = GL_LINEAR_MIPMAP_LINEAR;
		magnification_filter = GL_LINEAR;
		break;
	case TextureFilter::TFAnisotropic2:
		minification_filter = GL_LINEAR_MIPMAP_LINEAR;
		magnification_filter = GL_LINEAR;
		max_anisotropy = 2.0f;
		break;
	case TextureFilter::TFAnisotropic4:
		minification_filter = GL_LINEAR_MIPMAP_LINEAR;
		magnification_filter = GL_LINEAR;
		max_anisotropy = 4.0f;
	case TextureFilter::TFAnisotropic8:
		minification_filter = GL_LINEAR_MIPMAP_LINEAR;
		magnification_filter = GL_LINEAR;
		max_anisotropy = 8.0f;
		break;
	case TextureFilter::TFAnisotropic16:
		minification_filter = GL_LINEAR_MIPMAP_LINEAR;
		magnification_filter = GL_LINEAR;
		max_anisotropy = 16.0f;
		break;
	default:
		// Programming error, just crash
		App::panic("Unknown texture filter mode");
	}

	// Limit the setting to highest supported.
	max_anisotropy = (max_anisotropy <= max_anisotropy_supported)
	                     ? max_anisotropy
	                     : max_anisotropy_supported;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnification_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minification_filter);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
	                max_anisotropy);
	check_for_errors_gl();

	GLenum format = (texture.has_alpha) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0,
	             format, // Just do the same format as the internal one.
	             GL_UNSIGNED_BYTE, texture.data.data());
	check_for_errors_gl();
	if (texture.has_mipmap()) {
		glGenerateMipmap(GL_TEXTURE_2D);
		check_for_errors_gl();
	}
}

void OpenGLTexture::use(int texture_number) {
	glActiveTexture(GL_TEXTURE0 + texture_number);
	check_for_errors_gl();
	glBindTexture(GL_TEXTURE_2D, this->texture_binding);
	check_for_errors_gl();
}

void OpenGLTexture::destroy() {
	glDeleteTextures(1, &this->texture_binding);
	check_for_errors_gl();
}
