#pragma once

#include <glad/glad.h>
#include "ShaderProgram.hpp"
#include "Uniform.hpp"

struct Transform {
	Uniform<GLfloat, 3> position;
	Uniform<GLfloat, 3> scale;
	Uniform<GLfloat, 3> rotation;

	Transform(){}

	void New(const ShaderProgram& program) {
		position = Uniform<GLfloat, 3>(program.GetID(), "u_position");
		scale = Uniform<GLfloat, 3>(program.GetID(), "u_scale", 1.0f);
		rotation = Uniform<GLfloat, 3>(program.GetID(), "u_rotation");
	}

	void Update() {
		position.Update();
		scale.Update();
		rotation.Update();
	}
};