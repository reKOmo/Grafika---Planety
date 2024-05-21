#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // Dodano dla glm::rotate i glm::translate
#include <cmath> // Dodano dla funkcji sin i cos

#include "Camera.h"
#include "Model.h"
#include "Lights.h"

const int width = 1280;
const int height = 720;

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

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
    glEnable(GL_MULTISAMPLE);

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("src/shaders/default.vert", "src/shaders/default.frag");
    // Creates camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    Lights lights;
    PointLight p;
    p.position = { 2.0, 2.0, 2.0 };
    lights.addPointLight(p);

    // Loading models
    Model mercury("resources/mercury/mercury.fbx");
    Model venus("resources/venus/venus.fbx");
    Model mars("resources/mars/mars.fbx");
    Model saturn("resources/saturn/saturn.fbx");
    Model alien("resources/alien/alien.fbx");
    Model earth("resources/earth/earth.fbx");
    Model sun("resources/sun/sun.fbx");
    Model sky("resources/sky/sky.fbx");

    //Spot do testowania
    Model spot("resources/spot/spot.fbx");
    spot.meshes[0].material.ambient = glm::vec3(0.9, 0.9, 0.3);
    spot.meshes[0].material.specular = { 0.0, .0, .0 };

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

    float totalTime = 0;

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
        lights.setLights(shaderProgram);

        //Sky
        sky.position = glm::vec3(15.0f, 15.0f, 15.0f);
        //sky.scale = glm::vec3(40.0f, 40.0f, 40.0f);
        sky.Draw(shaderProgram);

        // Mercury
        float mercuryAngle = mercurySpeed * currentFrame;
        mercury.position = glm::vec3(mercuryOrbitRadius * sin(mercuryAngle), 0.0f, mercuryOrbitRadius * cos(mercuryAngle));
        mercury.Draw(shaderProgram);

        // Venus
        float venusAngle = venusSpeed * currentFrame;
        venus.position = glm::vec3(venusOrbitRadius * sin(venusAngle), 0.0f, venusOrbitRadius * cos(venusAngle));
        venus.Draw(shaderProgram);

        // Mars
        float marsAngle = marsSpeed * currentFrame;
        mars.position = glm::vec3(marsOrbitRadius * sin(marsAngle), 0.0f, marsOrbitRadius * cos(marsAngle));
        mars.Draw(shaderProgram);

        // Saturn
        float saturnAngle = saturnSpeed * currentFrame;
        saturn.position = glm::vec3(saturnOrbitRadius * sin(saturnAngle), 0.0f, saturnOrbitRadius * cos(saturnAngle));
        saturn.Draw(shaderProgram);

        // Alien
        float alienAngle = alienSpeed * currentFrame;
        alien.position = glm::vec3(alienOrbitRadius * sin(alienAngle), 0.0f, alienOrbitRadius * cos(alienAngle));
        alien.Draw(shaderProgram);
                 
        // Earth
        float earthAngle = earthSpeed * currentFrame;
        earth.position = glm::vec3(earthOrbitRadius * sin(earthAngle), 0.0f, earthOrbitRadius * cos(earthAngle));
        earth.scale = glm::vec3(0.025f, 0.025f, 0.025f);
        earth.Draw(shaderProgram);

        //Sun
        sun.position = glm::vec3(0.0f, 0.0f, 0.0f);
        sun.Draw(shaderProgram);

        /*
        spot.rotation.y += .5f * deltaTime;
        spot.Draw(shaderProgram);
        */
        if (totalTime < 0.3) {
            lights.pointLights[0].diffuse = { 0.0, 1.0, .0 };
        }
        else if (totalTime < 0.6) {
            lights.pointLights[0].diffuse = { 1.0, 0.0, .0 };
        }
        else if (totalTime < 0.9) {
            lights.pointLights[0].diffuse = { 0.0, 0.0, 1.0 };
        }
        else {
            totalTime = 0.0;
            lights.pointLights[0].diffuse = { 0.0, 1.0, .0 };
        }
        totalTime += deltaTime;
        lights.drawLights(camera.cameraMatrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
