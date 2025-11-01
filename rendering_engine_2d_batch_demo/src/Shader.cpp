
#include "Shader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

static std::string readFile(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) throw std::runtime_error("Failed to open file: " + path);
    std::stringstream ss; ss << ifs.rdbuf();
    return ss.str();
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vsrc = readFile(vertexPath);
    std::string fsrc = readFile(fragmentPath);

    auto compile = [](const std::string& src, GLenum type) -> unsigned int {
        unsigned int id = glCreateShader(type);
        const char* csrc = src.c_str();
        glShaderSource(id, 1, &csrc, nullptr);
        glCompileShader(id);
        int ok; glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            char log[1024]; glGetShaderInfoLog(id, 1024, nullptr, log);
            std::string err = (type==GL_VERTEX_SHADER? "VERTEX" : "FRAGMENT");
            throw std::runtime_error(err + std::string(" shader compile failed: ") + log);
        }
        return id;
    };

    unsigned int vs = compile(vsrc, GL_VERTEX_SHADER);
    unsigned int fs = compile(fsrc, GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    int ok; glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024]; glGetProgramInfoLog(program, 1024, nullptr, log);
        throw std::runtime_error(std::string("Program link failed: ") + log);
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    if (program) glDeleteProgram(program);
}

void Shader::bind() const { glUseProgram(program); }
void Shader::unbind() const { glUseProgram(0); }

int Shader::uniformLocation(const std::string& name) const {
    int loc = glGetUniformLocation(program, name.c_str());
    if (loc == -1) {
        // std::cerr << "Warning: uniform '" << name << "' not found\n";
    }
    return loc;
}

void Shader::setMat4(const std::string& name, const glm::mat4& m) {
    glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, glm::value_ptr(m));
}
