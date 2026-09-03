#pragma once

#include <vector>

#include "assets/types.hpp"
#include "uniform.hpp"

class Material {
private:
	AssetID shader;
	std::vector<Uniform> uniforms;
	std::vector<AssetID> textures;
public:
	explicit Material(AssetID shader): shader(shader) {}
	virtual void prepare() = 0;
};