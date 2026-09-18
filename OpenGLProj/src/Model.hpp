#pragma once

#include <glad/glad.h>
#include <vector>

using namespace std;

class Model {
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	GLuint count = 0;
	GLenum type = GL_STATIC_DRAW;

	void UpdateData(const vector<GLfloat>& vertices, const vector<GLuint>& indices, GLenum type = GL_STATIC_DRAW) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), type);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), type);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertices[0]) * 3, nullptr);
		glEnableVertexAttribArray(0);
		this->count = indices.size();
	}
public:
	Model(){}

	void New(const vector<GLfloat>& vertices, const vector<GLuint>& indices, GLenum type = GL_STATIC_DRAW) {
		cout << "Creating model" << endl;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		this->type = type;

		Bind();

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		UpdateData(vertices, indices, type);
	}

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

	void Bind() const {
		glBindVertexArray(VAO);
	}

	void Unbind() const {
		glBindVertexArray(0);
	}

	GLuint GetCount() const {
		return count;
	}

	GLenum GetType() const {
		return type;
	}

	~Model() {
		cout << "Deleting model" << endl;

		Unbind();

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
};