#pragma once
#include "shaderClass.h"
#include "Mesh.h"
#include <assimp/scene.h>

class Model
{
public:
    Model(char* path)
    {
        loadModel(path);
        position = { 0.0f, 0.0f, 0.0f };
        rotation = { 0.0f, 0.0f, 0.0f };
        scale = { 1.0f, 1.0f, 1.0f };
    }
    void Draw(Shader& shader, float currentFrame, float selfRotationSpeed);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    std::vector<Mesh> meshes;
private:
    // model data
    std::string directory;


    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};