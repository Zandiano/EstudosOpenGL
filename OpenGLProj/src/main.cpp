#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <fstream> 
#include <string> 

static void ReziseWindow(GLFWwindow* window, int Width, int Height) {
	glViewport(0, 0, Width, Height); 
} 

int main() { 
	const int ScreenWidth = 800; 
	const int ScreenHeight = 800; 

	glfwInit(); 

	GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Window", NULL, NULL); 

	if (window == NULL) { 
		std::cout << "Falhou" << std::endl; glfwTerminate(); return -1; 
	} 

	glfwMakeContextCurrent(window); 

	gladLoadGL(glfwGetProcAddress); 

	glViewport(0, 0, ScreenWidth, ScreenHeight); 

	glfwSetWindowSizeCallback(window, ReziseWindow); 

	//vector<GLfloat> vertices = { 
		 //-0.25f, -0.25f, 0.0f, 
		 //-0.25f, 0.25f, 0.0f, 
		 //0.25f, 0.25f, 0.0f, 
		 //0.25f, -0.25f, 0.0f 
	// }; 
	//vector<GLuint> indices{ 0,1,2, 2,3,0, }; 
	
	//Object square(vertices, indices, GL_STATIC_DRAW, "default.vert", "default.frag"); 
	//Object square2(vertices, indices, GL_STATIC_DRAW, "default.vert", "default.frag"); 
	//square.SetScale(0.5f, 0.5f, 1.0f); square2.SetScale(0.3f, 0.3f, 1.0f); 
	
	//square2.SetPosition(0.8f, 0.8f, 0.0f); GLint camLoc[2] = { 0 }; 
	//square.GetShader()->GetUniformLoc("u_camera", camLoc[0]); 
	//square2.GetShader()->GetUniformLoc("u_camera", camLoc[1]); 

	float cameraPos[3] = { 0,0,0 }; 
	while (!glfwWindowShouldClose(window)) { 
		glClearColor(0.1f, 0.01f, 0.01f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT); 
		cameraPos[1] += 0.01f * abs(glfwGetKey(window, GLFW_KEY_W)); 
		cameraPos[0] -= 0.01f * abs(glfwGetKey(window, GLFW_KEY_A)); 
		
		cameraPos[1] -= 0.01f * abs(glfwGetKey(window, GLFW_KEY_S)); 
		cameraPos[0] += 0.01f * abs(glfwGetKey(window, GLFW_KEY_D)); 

		//square.SetPosition(cameraPos[0], cameraPos[1], 1.0f); 
		//square.GetShader()->SetUniform(camLoc[0], 1, cameraPos, 3); 
		//square2.GetShader()->SetUniform(camLoc[1], 1, cameraPos, 3); 
		//square.Draw(); 
		//square2.Draw(); 

		glfwSwapBuffers(window); 
		glfwPollEvents(); 
	} 

	//square.GetShader()->Delete(); 
	//square2.GetShader()->Delete();

	glfwDestroyWindow(window); 
	glfwTerminate(); 
	return 0; 
}