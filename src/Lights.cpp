#pragma once
#include "Lights.h"
#include <string>
#include "shaderClass.h"

void Lights::addPointLight(PointLight p)
{
	pointLights.push_back(p);
}

void Lights::setLights(Shader& s)
{
    s.setInt("totalPointLights", pointLights.size());
    std::string attribPrefix = "pointLights[";
    for (int i = 0; i < pointLights.size(); i++) {
        s.setVec3(attribPrefix + std::to_string(i) + "].position", pointLights[i].position);
        s.setVec3(attribPrefix + std::to_string(i) + "].ambient", pointLights[i].ambient);
        s.setVec3(attribPrefix + std::to_string(i) + "].diffuse", pointLights[i].diffuse);
        s.setVec3(attribPrefix + std::to_string(i) + "].specular", pointLights[i].specular);
        s.setFloat(attribPrefix + std::to_string(i) + "].constant", pointLights[i].constant);
        s.setFloat(attribPrefix + std::to_string(i) + "].linear", pointLights[i].linear);
        s.setFloat(attribPrefix + std::to_string(i) + "].quadratic", pointLights[i].quadratic);
	}
}

void Lights::drawLights(glm::mat4& camMatrix)
{
    shader.Activate();
    shader.setMat4("camMatrix", camMatrix);
    glm::vec4 pointColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    shader.setVec4("color", pointColor);
    for (unsigned int i = 0; i < pointLights.size(); i++)
    {
        lightModel.position = pointLights[i].position;
        lightModel.Draw(shader);
    }
}
