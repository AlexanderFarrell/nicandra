#pragma once

#include "assets/types.hpp"
#include "uniform.hpp"

#include <vector>

class Drawable {
	AssetID material_id;
	AssetID mesh_id;
	std::vector<Uniform> uniforms;
};