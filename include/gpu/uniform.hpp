#pragma once

#include <string>
#include <variant>

#include <glm/glm.hpp>

enum UniformKind {
	Vector4,
	Vector3,
	Vector2,
	Scalar,
	Scalar_int,
	Matrix4x4,
};



class Uniform {
	std::string name;
	UniformKind kind;
	std::variant<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat4> value;

	Uniform(const std::string& name, int scalar_int);
	Uniform(const std::string& name, float scalar);
	Uniform(const std::string& name, glm::vec2 vec2);
	Uniform(const std::string& name, glm::vec3 vec3);
	Uniform(const std::string& name, glm::vec4 vec4);
	Uniform(const std::string& name, glm::mat4 mat4);
};

class GPUUniform {
	virtual void buffer(const Uniform& uniform) = 0;
	virtual void use(const Uniform& uniform) = 0;
};
