#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // Dodano dla glm::rotate i glm::translate
#include <cmath> // Dodano dla funkcji sin i cos

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

    // Loading models
    Model mercury("resources/mercury/mercury.fbx");
    Model venus("resources/venus/venus.fbx");
    Model mars("resources/mars/mars.fbx");
    Model saturn("resources/saturn/saturn.fbx");
    Model alien("resources/alien/alien.fbx");
    Model earth("resources/earth/earth.fbx");
    Model sun("resources/sun/sun.fbx");

    // Orbital radii
    float mercuryOrbitRadius = 25.0f;
    float venusOrbitRadius = 35.0f;
    float marsOrbitRadius = 45.0f;
    float saturnOrbitRadius = 55.0f;
    float alienOrbitRadius = 65.0f;
    float earthOrbitRadius = 75.0f;

    // Angular velocities (in radians per second)
    float mercurySpeed = 1.0f;
    float venusSpeed = 0.8f;
    float marsSpeed = 0.6f;
    float saturnSpeed = 0.4f;
    float alienSpeed = 0.2f;
    float earthSpeed = 0.1f;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 200.0f);

        // Rysowanie modeli
        shaderProgram.Activate();
        camera.Matrix(shaderProgram, "camMatrix");
        shaderProgram.setVec4("color", glm::vec4(0.8, 0.079, 0.262, 1.0));

        // Mercury
        float mercuryAngle = mercurySpeed * currentFrame;
        mercury.position = glm::vec3(mercuryOrbitRadius * cos(mercuryAngle), 0.0f, mercuryOrbitRadius * sin(mercuryAngle));
        mercury.rotation.x = 90.f;
        mercury.Draw(shaderProgram);

        // Venus
        float venusAngle = venusSpeed * currentFrame;
        venus.position = glm::vec3(venusOrbitRadius * cos(venusAngle), 0.0f, venusOrbitRadius * sin(venusAngle));
        venus.rotation.x = 90.0f;
        venus.Draw(shaderProgram);

        // Mars
        float marsAngle = marsSpeed * currentFrame;
        mars.position = glm::vec3(marsOrbitRadius * cos(marsAngle), 0.0f, marsOrbitRadius * sin(marsAngle));
        mars.rotation.x = 90.0f;
        mars.Draw(shaderProgram);

        // Saturn
        float saturnAngle = saturnSpeed * currentFrame;
        saturn.position = glm::vec3(saturnOrbitRadius * cos(saturnAngle), 0.0f, saturnOrbitRadius * sin(saturnAngle));
        saturn.rotation.x = 90.0f;
        saturn.Draw(shaderProgram);

        // Alien
        float alienAngle = alienSpeed * currentFrame;
        alien.position = glm::vec3(alienOrbitRadius * cos(alienAngle), 0.0f, alienOrbitRadius * sin(alienAngle));
        alien.rotation.x = 90.0f;
        alien.Draw(shaderProgram);

        // Earth
        float earthAngle = earthSpeed * currentFrame;
        earth.position = glm::vec3(earthOrbitRadius * cos(earthAngle), 0.0f, earthOrbitRadius * sin(earthAngle));
        earth.rotation.x = 90.0f;
        earth.scale = glm::vec3(0.025f, 0.025f, 0.025f);
        earth.Draw(shaderProgram);

        //Sun
        sun.position = glm::vec3(0.0f, 0.0f, 0.0f);
        sun.rotation.x = 90.0f;
        sun.Draw(shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
