#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include "Shader.hpp"

class ShaderProgram {
private:
	GLuint ID = 0;

public:
	ShaderProgram(const string& VertexFP, const string& FragmentFP) {
		ID = glCreateProgram();

		Shader vertex(VertexFP, GL_VERTEX_SHADER);
		Shader fragment(FragmentFP, GL_FRAGMENT_SHADER);

		glAttachShader(ID, vertex.GetID());
		glAttachShader(ID, fragment.GetID());

		glLinkProgram(ID);

		GLint success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);

		if (!success) {
			GLint length;
			glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &length);

			string log(length, '\0');

			glGetProgramInfoLog(
				ID,
				length,
				nullptr,
				log.data()
			);

			cout << "Shader program linking failed:\n";
			cout << log << endl;
		}
	}

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	GLuint GetID() const {
		return ID;
	}

	~ShaderProgram() {
		if (ID != 0) {
			glDeleteProgram(ID);
		}
	}

};