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
    }
    void Draw(Shader& shader);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;


    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};