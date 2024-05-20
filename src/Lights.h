#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "shaderClass.h"
#include "Model.h"

struct PointLight {
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    glm::vec3 ambient = { 0.05f, 0.05f, 0.05f };
    glm::vec3 diffuse = { 0.8f, 0.8f, 0.8f };
    glm::vec3 specular = { 1.0f, 1.0f, 1.0f };
};

class Lights {
public:
    Lights() : shader("src/shaders/color.vert", "src/shaders/color.frag"), lightModel("resources/cube.fbx") {}
    void addPointLight(PointLight p);
    void setLights(Shader& s);
    void drawLights(glm::mat4& cameraMatrix);
    std::vector<PointLight> pointLights;
private:
    Shader shader;
    Model lightModel;
};