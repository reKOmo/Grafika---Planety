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
    Shader flatShaderProgram("src/shaders/flat.vert", "src/shaders/flat.frag");
    Shader starShader("src/shaders/flat.vert", "src/shaders/stars.frag");
    // Creates camera object
    Camera camera(width, height, glm::vec3(25.0f, 15.0f, 90.0f));

    Lights lights;
    PointLight p;
    glm::vec3 lightColor(1.0f, 0.5f, 0.31f);
    p.diffuse = lightColor * 0.5f;
    p.ambient = lightColor * 0.01f;
    p.specular = { 1.0, 1.0, 1.0 };
    p.position = { .0, .0, .0 };
    p.linear = 0.007;
    p.quadratic = 0.0002;
    p.constant = 1.0;
    lights.addPointLight(p);

    PointLight p2;
    p2.linear = 0.35f;
    p2.quadratic = 0.2f;
    glm::vec3 spotLightColor(1.0f, 0.0f, 0.0f);
    p2.diffuse = spotLightColor * 0.7f;
    p2.ambient = spotLightColor * 0.00f;
    p2.specular = { 1.0, 1.0, 1.0 };
    float timeForLight = 0.0;
    lights.addPointLight(p2);

    // Loading models
    Model mercury("resources/mercury/mercury.fbx");
    Model venus("resources/venus/venus.fbx");
    Model mars("resources/mars/mars.fbx");
    Model saturn("resources/saturn/saturn.fbx");
    Model alien("resources/alien/alien.fbx");
    Model earth("resources/earth/earth.fbx");
    Model sun("resources/sun/sun.fbx");
    Model sky("resources/sphere/sphere.fbx");
    Model spot("resources/spot/spot.fbx");

    sky.position = glm::vec3(0.0f, 0.0f, 0.0f);
    sky.scale = glm::vec3(1500.0f);

    // Orbital radii
    float mercuryOrbitRadius = 25.0f;
    float venusOrbitRadius = 35.0f;
    float marsOrbitRadius = 45.0f;
    float saturnOrbitRadius = 75.0f;
    float alienOrbitRadius = 65.0f;
    float earthOrbitRadius = 55.0f;

    // Angular velocities (in radians per second)
    float mercurySpeed = 1.0f;
    float venusSpeed = 0.8f;
    float marsSpeed = 0.6f;
    float saturnSpeed = 0.4f;
    float alienSpeed = 0.2f;
    float earthSpeed = 0.1f;

    /*float mercurySpeed = .0f;
    float venusSpeed = 0.0f;
    float marsSpeed = 0.0f;
    float saturnSpeed = 0.0f;
    float alienSpeed = 0.0f;
    float earthSpeed = 0.0f;*/

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

        camera.Inputs(window, currentFrame);  // Przekazanie deltaTime
        camera.updateMatrix(60.0f, 0.1f, 3000.0f);

        // Rysowanie modeli
        shaderProgram.Activate();
        camera.Matrix(shaderProgram, "camMatrix");
        lights.setLights(shaderProgram);

        // Mercury
        float mercuryAngle = mercurySpeed * currentFrame;
        mercury.position = glm::vec3(mercuryOrbitRadius * sin(mercuryAngle), 0.0f, mercuryOrbitRadius * cos(mercuryAngle));
        mercury.Draw(shaderProgram, currentFrame, -0.4f);

        // Venus
        float venusAngle = venusSpeed * currentFrame;
        venus.position = glm::vec3(venusOrbitRadius * sin(venusAngle), 0.0f, venusOrbitRadius * cos(venusAngle));
        venus.Draw(shaderProgram, currentFrame, -0.8f);

        // Mars
        float marsAngle = marsSpeed * currentFrame;
        mars.position = glm::vec3(marsOrbitRadius * sin(marsAngle), 0.0f, marsOrbitRadius * cos(marsAngle));
        mars.Draw(shaderProgram, currentFrame, -1.4f);

        // Saturn
        float saturnAngle = saturnSpeed * currentFrame;
        saturn.position = glm::vec3(saturnOrbitRadius * sin(saturnAngle), 0.0f, saturnOrbitRadius * cos(saturnAngle));
        saturn.Draw(shaderProgram, currentFrame, -0.9f);

        // Alien
        float alienAngle = alienSpeed * currentFrame;
        alien.position = glm::vec3(alienOrbitRadius * sin(alienAngle), 0.0f, alienOrbitRadius * cos(alienAngle));
        alien.Draw(shaderProgram, currentFrame, -0.7f);

        // Earth
        float earthAngle = earthSpeed * currentFrame;
        earth.position = glm::vec3(earthOrbitRadius * sin(earthAngle), 0.0f, earthOrbitRadius * cos(earthAngle));
        earth.scale = glm::vec3(0.025f, 0.025f, 0.025f);
        earth.Draw(shaderProgram, currentFrame, -4.0f);

        //Spot
        spot.position = earth.position;
        spot.position.x += 5;
        lights.pointLights[1].position = spot.position - glm::vec3(1.0, .0, .0);
        if (timeForLight < 0.1) {
            lights.pointLights[1].diffuse = { 1.0, .0, .0 };
        }
        else if (timeForLight < 0.2) {
            lights.pointLights[1].diffuse = { 0.0, 1.0, .0 };
        }
        else if (timeForLight < 0.3) {
            lights.pointLights[1].diffuse = { .0, .0, 1.0 };
        }
        else {
            timeForLight = 0.0;
            lights.pointLights[1].diffuse = { 1.0, .0, .0 };
        }
        timeForLight += deltaTime;
        spot.Draw(shaderProgram, 1, glm::radians(90.0f));


        flatShaderProgram.Activate();
        camera.Matrix(flatShaderProgram, "camMatrix");
        //Sun
        sun.position = glm::vec3(0.0f, 0.0f, 0.0f);
        sun.Draw(flatShaderProgram, currentFrame, 1.0f);

        //Sky
        starShader.Activate();
        camera.Matrix(starShader, "camMatrix");
        starShader.setFloat("time", currentFrame);
        sky.Draw(starShader, currentFrame, 0.0f);

        //lights.drawLights(camera.cameraMatrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
