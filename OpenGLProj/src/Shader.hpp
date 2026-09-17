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
			source += buffer + "\n";
		}
		return true;
	}

public:
	Shader(const string& filepath,GLenum type) {
		ID = glCreateShader(type);
		string tempSource = "";
		if (!GetSource(filepath, tempSource)) {
			cout << "Unable to create shader" << endl;
			return;
		}
		const char* tempSourceChar = tempSource.c_str();
		glShaderSource(ID, 1, &tempSourceChar, NULL);
		glCompileShader(ID);
	}

	GLuint GetID() const {
		return ID;
	}

	~Shader() {
		if (ID != 0) {
			glDeleteShader(ID);
		}
	}
};