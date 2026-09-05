#pragma once

#include <vector>

#include "assets/types.hpp"
#include "uniform.hpp"
#include "util/data/slotmap.hpp"

class GPUMaterial {
	virtual void prepare() = 0;
};

class Material {
private:
	AssetID shader;
	std::vector<Uniform> uniforms;
	std::vector<AssetID> textures;
	GenIndex gpu_material;
public:
	explicit Material(AssetID shader) : shader(shader) {}
};
