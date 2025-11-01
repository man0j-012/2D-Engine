
#pragma once
#include <vector>
#include <array>
#include <glm/glm.hpp>

struct Quad {
    float pos[2];
    float size[2];
    float color[4];
};

struct Camera2D {
    float x = 0.0f;
    float y = 0.0f;
};

class Renderer2D {
public:
    explicit Renderer2D(size_t maxVertices);
    ~Renderer2D();

    void setViewSize(float width, float height);
    glm::mat4 getProjection() const;
    glm::mat4 getView() const;

    void begin();
    void pushQuad(const Quad& q);
    void flush();

    Camera2D camera;

private:
    unsigned int vao = 0, vbo = 0;
    size_t maxVertices;
    std::vector<float> vertexData; // x, y, r, g, b, a
    float viewW = 1280.0f, viewH = 720.0f;

    void initGL();
};
