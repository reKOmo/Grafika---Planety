#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shaderClass.h"
#include "Texture.h"
#include "Material.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


class Mesh {
public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Material material;

    Mesh() {
        vertices = {};
        indices = {};
        textures = {};
    }
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material m);
    void Draw(Shader& shader, glm::mat4& model);
private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};