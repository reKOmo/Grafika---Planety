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


	//Ladownie modelu
	Model mercury("resources/mercury/mercury.fbx");
	Model venus("resources/venus/venus.fbx");
	Model mars("resources/mars/mars.fbx");
	Model saturn("resources/saturn/saturn.fbx");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		//Rysowanie modelu
		shaderProgram.Activate();
		camera.Matrix(shaderProgram, "camMatrix");
		//ustawianie pozycji
		glm::vec3 mercuryPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4 mercuryModel = glm::mat4(1.0f);
		mercuryModel = glm::translate(mercuryModel, mercuryPosition);
		//obracanie
		mercuryModel = glm::rotate(mercuryModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shaderProgram.setMat4("model", mercuryModel);
		shaderProgram.setVec4("color", glm::vec4(0.8, 0.079, 0.262, 1.0));
		mercury.Draw(shaderProgram);

		glm::vec3 venusPosition = glm::vec3(5.0f, 0.0f, 0.0f);
		glm::mat4 venusModel = glm::mat4(1.0f);
		venusModel = glm::translate(venusModel, venusPosition);
		//obracanie
		venusModel = glm::rotate(venusModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shaderProgram.setMat4("model", venusModel);
		shaderProgram.setVec4("color", glm::vec4(0.8, 0.079, 0.262, 1.0));
		venus.Draw(shaderProgram);

		glm::vec3 marsPosition = glm::vec3(15.0f, 0.0f, 0.0f);
		glm::mat4 marsModel = glm::mat4(1.0f);
		marsModel = glm::translate(marsModel, marsPosition);
		//obracanie
		marsModel = glm::rotate(marsModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shaderProgram.setMat4("model", marsModel);
		shaderProgram.setVec4("color", glm::vec4(0.8, 0.079, 0.262, 1.0));
		mars.Draw(shaderProgram);

		glm::vec3 saturnPosition = glm::vec3(35.0f, 0.0f, 0.0f);
		glm::mat4 saturnModel = glm::mat4(1.0f);
		saturnModel = glm::translate(saturnModel, saturnPosition);
		//obracanie
		saturnModel = glm::rotate(saturnModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shaderProgram.setMat4("model", saturnModel);
		shaderProgram.setVec4("color", glm::vec4(0.8, 0.079, 0.262, 1.0));
		saturn.Draw(shaderProgram);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}