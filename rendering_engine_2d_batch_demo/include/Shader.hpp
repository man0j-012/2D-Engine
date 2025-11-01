
#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setMat4(const std::string& name, const glm::mat4& m);

private:
    unsigned int program = 0;
    int uniformLocation(const std::string& name) const;
};
