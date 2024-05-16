#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include<glm/glm.hpp>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, glm::vec2& value) const;
	void setVec3(const std::string& name, glm::vec3& value) const;
	void setVec4(const std::string& name, glm::vec4& value) const;
	void setMat4(const std::string& name, glm::mat4& value) const;
private:
	void compileErrors(unsigned int shader, const char* type);
};
