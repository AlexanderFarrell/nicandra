#pragma once

#include "types.hpp"

#include "../gpu/drawable.hpp"
#include "../gpu/material.hpp"
#include "../gpu/mesh.hpp"
#include "../gpu/shader.hpp"
#include "../gpu/texture.hpp"
#include "../gpu/uniform.hpp"

class Assets {
public:
	SlotMap<Drawable> drawables;
	SlotMap<Material> materials;
	SlotMap<Mesh> meshes;
	SlotMap<Shader> shaders;
	SlotMap<Texture> textures;
};