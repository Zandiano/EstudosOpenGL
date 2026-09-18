#pragma once

#include "Model.hpp"
#include "ShaderProgram.hpp"
#include "Transform.hpp"
#include <vector>
#include <map>

using namespace std;

class Object {
private:
	Model model;
	ShaderProgram shader;
	Uniform<GLfloat, 3> camera;

public:
	Transform transform;

	Object(const vector<GLfloat>& vertices, const vector<GLuint>& indices, GLenum type, const string& VertexFP, const string& FragmentFP) {
		cout << "Creating object" << endl;
		
		model.New(vertices, indices, type);
		shader.New(VertexFP, FragmentFP);
		transform.New(shader);

		camera.New(shader.GetID(), "u_camera");
	}
	
	GLuint ShaderID() {
		return shader.GetID();
	}

	void Update(GLfloat cameraPos[3]) {
		shader.Bind();
		camera.Set(cameraPos[0], cameraPos[1], cameraPos[2]);
		camera.Update();
		transform.Update();
	}

	void Draw(GLenum mode = GL_TRIANGLES) {
		shader.Bind();
		model.Bind();
		glDrawElements(mode, model.GetCount(), GL_UNSIGNED_INT, NULL);
	}
};