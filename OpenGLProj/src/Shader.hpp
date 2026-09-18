#pragma once

#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Shader {
private:
	GLuint ID = 0;

	bool GetSource(const string& filepath, string& source) {
		cout << "Reading: " << filepath << endl;
		ifstream file(filepath);
		if (!file.is_open()) {
			cout << "Invalid filepath" << endl;
			return false;
		}
		string buffer;
		while (getline(file, buffer)) {
			cout << buffer << endl;
			source += buffer + "\n";
		}
		return true;
	}

public:
	Shader(const string& filepath,GLenum type) {
		ID = glCreateShader(type);
		cout << "Creating shader: " << ID << endl;
		string tempSource = "";
		if (!GetSource(filepath, tempSource)) {
			cout << "Unable to create shader" << endl;
			return;
		}
		const char* tempSourceChar = tempSource.c_str();
		glShaderSource(ID, 1, &tempSourceChar, NULL);

		glCompileShader(ID);
		GLint success;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(ID, 512, NULL, infoLog);

			cout << "Shader compilation failed:\n";
			cout << infoLog << endl;
		}
	}

	GLuint GetID() const {
		return ID;
	}

	~Shader() {
		if (ID != 0) {
			cout << "Deleting shader" << endl;
			glDeleteShader(ID);
		}
	}
};