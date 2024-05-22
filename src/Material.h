#pragma once
#include <glm/glm.hpp>

/*
    Only color
*/
struct BasicMaterial {
    glm::vec3 diffuse;

    void setValues(Shader s) {
        s.setVec3("color", diffuse);
    }
};


/*
    Basic material
*/
struct Material : BasicMaterial {
    glm::vec3 ambient;
    glm::vec3 specular;
    float shininess;
    float shineStrength;
    void setValues(Shader s) {
        s.setVec3("ambientColor", ambient);
        s.setVec3("specularColor", specular);
        s.setVec3("color", diffuse);
        s.setFloat("shininess", shininess);
        s.setFloat("shineStrength", shineStrength);
    }
};