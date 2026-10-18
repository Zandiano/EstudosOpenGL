#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>

#include "Object.hpp"
#include "Uniform.hpp"

using namespace std;

static void ReziseWindow(GLFWwindow* window, int Width, int Height) {
	glViewport(0, 0, Width, Height); 
} 

int main() { 
	const int ScreenWidth = 800; 
	const int ScreenHeight = 800; 

	glfwInit(); 

	GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Window", NULL, NULL); 

	if (window == NULL) { 
		std::cout << "Falhou" << std::endl; 
		glfwTerminate(); 
		return -1; 
	} 

	glfwMakeContextCurrent(window); 

	gladLoadGL(glfwGetProcAddress); 

	glViewport(0, 0, ScreenWidth, ScreenHeight); 

	glfwSetWindowSizeCallback(window, ReziseWindow); 

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);

	vector<GLfloat> vertices = { 
		 -0.25f, -0.25f, 0.0f, 
		 -0.25f, 0.25f, 0.0f, 
		 0.25f, 0.25f, 0.0f, 
		 0.25f, -0.25f, 0.0f 
	 }; 
	vector<GLuint> indices{ 
		0,1,2, 
		2,3,0, 
	}; 

	vector<GLfloat> vertices2 = {
		 -0.0f, -0.25f, 0.0f,
		 -0.25f, 0.25f, 0.0f,
		 0.25f, 0.25f, 0.0f,
	};
	vector<GLuint> indices2{
		0,1,2
	};

	{

		Object square(vertices, indices, GL_STATIC_DRAW, "default.vert", "default.frag");
		Object square2(vertices2, indices2, GL_STATIC_DRAW, "default.vert", "default.frag");

		square.transform.scale.Set(0.5f, 0.5f, 1.0f);
		square2.transform.scale.Set(0.3f, 0.3f, 1.0f);

		square2.transform.position.Set(0.8f, 0.8f, 0.0f);

		Uniform<GLfloat, 4> color(square.ShaderID(), "u_color");
		Uniform<GLfloat, 4> color2(square2.ShaderID(), "u_color");

		color.Set(0.5f, 0.2f, 0.8f, 1.0f);
		color2.Set(0.1f, 0.1f, 0.2f, 1.0f);

		color.Update(square.ShaderID());
		color2.Update(square2.ShaderID());

		float cameraPos[3] = { 0,0,0 };
		while (!glfwWindowShouldClose(window)) {
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			cameraPos[1] += 0.01f * abs(glfwGetKey(window, GLFW_KEY_W));
			cameraPos[1] -= 0.01f * abs(glfwGetKey(window, GLFW_KEY_S));

			cameraPos[0] += 0.01f * abs(glfwGetKey(window, GLFW_KEY_D));
			cameraPos[0] -= 0.01f * abs(glfwGetKey(window, GLFW_KEY_A));

			cameraPos[2] -= 0.01f * abs(glfwGetKey(window, GLFW_KEY_E));
			cameraPos[2] += 0.01f * abs(glfwGetKey(window, GLFW_KEY_Q));

			square.transform.position.Set(cameraPos[0], cameraPos[1], cameraPos[2]);
			square.Update(cameraPos);
			square2.Update(cameraPos);
			square.Draw();
			square2.Draw();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate(); 
	return 0; 
}