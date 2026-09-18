#pragma once

#include <glad/glad.h>
#include <string>
#include <array>
#include "ShaderProgram.hpp"

using namespace std;

template <typename T, int size>
class Uniform {
private:
	GLuint loc = 0;
	array<T,size> value;
public:
	Uniform(T fill = 0) {
		for (int i = 0; i < size; i++) {
			value[i] = fill;
		}
	}

	Uniform(GLuint programID, const string& name, T fill = 0) {
		New(programID, name, fill);
	}

	void New(GLuint programID, const string& name, T fill = 0) {
		loc = glGetUniformLocation(programID, name.c_str());
		cout << "Getting uniform loc: " << loc << endl;
		for (int i = 0; i < size; i++) {
			value[i] = fill;
		}
	}

	void Set(T newVal, int index = 0) {
		value[index] = newVal;
	}

	template <typename...Args>
	void Set(Args ...args) {
		//cout << "Setting new value to uniform: " << loc << endl;
		static_assert(sizeof...(Args) == size, "Incorrect qnt of arguments");
		value = { args... };
	}

	void Sum(double num, int index = 0) {
		this->value[index] += num;
	}

	void Mult(double num, int index = 0) {
		this->value[index] *= num;
	}

	Uniform& operator=(const Uniform<T, size>& newUniform) {
		loc = newUniform.loc;
		value = newUniform.value;

		return *this;
	}

	T Get(int index = 0) {
		return value[index];
	}

	T& GetAddres(int index = 0) {
		return value[index];
	}

	void Update(GLuint shaderID = 0) {
		if (shaderID != 0) {
			glUseProgram(shaderID);
		}

		//cout << "Updating uniform: " << loc << endl;

		if constexpr (std::is_same_v<T, float>) {

			if constexpr (size == 1)
				glUniform1fv(loc, 1, value.data());

			else if constexpr (size == 2)
				glUniform2fv(loc, 1, value.data());

			else if constexpr (size == 3)
				glUniform3fv(loc, 1, value.data());

			else if constexpr (size == 4)
				glUniform4fv(loc, 1, value.data());
		}

		else if constexpr (std::is_same_v<T, int>) {

			if constexpr (size == 1)
				glUniform1iv(loc, 1, value.data());

			else if constexpr (size == 2)
				glUniform2iv(loc, 1, value.data());

			else if constexpr (size == 3)
				glUniform3iv(loc, 1, value.data());

			else if constexpr (size == 4)
				glUniform4iv(loc, 1, value.data());
		}

		else if constexpr (std::is_same_v<T, unsigned int>) {

			if constexpr (size == 1)
				glUniform1uiv(loc, 1, value.data());

			else if constexpr (size == 2)
				glUniform2uiv(loc, 1, value.data());

			else if constexpr (size == 3)
				glUniform3uiv(loc, 1, value.data());

			else if constexpr (size == 4)
				glUniform4uiv(loc, 1, value.data());
		}
	}
};