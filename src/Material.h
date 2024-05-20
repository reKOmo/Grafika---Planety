#pragma once
#include <glm/glm.hpp>

/*
    Only color
*/
struct BasicMaterial {
    glm::vec3 diffuse;
};


/*
    Basic material
*/
struct Material : BasicMaterial {
    glm::vec3 ambient;
    glm::vec3 specular;
    float shininess;
    float shineStrength;
};