#pragma once

#include "gpu/uniform.hpp"

class OpenGLUniform: public GPUUniform {
	void buffer(const Uniform &uniform) override;
	void use(const Uniform &uniform) override;
};