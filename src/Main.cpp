#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Model.h"

const int width = 1280;
const int height = 720;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("src/shaders/flat.vert", "src/shaders/flat.frag");
	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model monkey("resources/test_monkey.fbx");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		shaderProgram.Activate();
		camera.Matrix(shaderProgram, "camMatrix");

		glm::vec3 monkeyPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4 monkeyModel = glm::mat4(1.0f);
		monkeyModel = glm::translate(monkeyModel, monkeyPosition);

		shaderProgram.setMat4("model", monkeyModel);

		shaderProgram.setVec4("color", glm::vec4(0.8, 0.079, 0.262, 1.0));
		monkey.Draw(shaderProgram);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}