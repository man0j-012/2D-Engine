
#include "Renderer2D.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

Renderer2D::Renderer2D(size_t maxVertices)
: maxVertices(maxVertices) {
    initGL();
    vertexData.reserve(maxVertices * 6); // conservative
}

Renderer2D::~Renderer2D() {
    if (vbo) glDeleteBuffers(1, &vbo);
    if (vao) glDeleteVertexArrays(1, &vao);
}

void Renderer2D::initGL() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    // Layout: vec2 position, vec4 color  => stride 6 floats
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)(sizeof(float)*2));

    glBindVertexArray(0);
}

void Renderer2D::setViewSize(float width, float height) {
    viewW = width; viewH = height;
}

glm::mat4 Renderer2D::getProjection() const {
    return glm::ortho(0.0f, viewW, 0.0f, viewH, -1.0f, 1.0f);
}

glm::mat4 Renderer2D::getView() const {
    return glm::translate(glm::mat4(1.0f), glm::vec3(-camera.x + viewW*0.5f, -camera.y + viewH*0.5f, 0.0f));
}

void Renderer2D::begin() {
    vertexData.clear();
}

void Renderer2D::pushQuad(const Quad& q) {
    // Build two triangles per quad; positions in screen space center-based
    float x = q.pos[0], y = q.pos[1];
    float hw = q.size[0]*0.5f, hh = q.size[1]*0.5f;
    float r=q.color[0],g=q.color[1],b=q.color[2],a=q.color[3];

    // Convert to screen coords (0..viewW, 0..viewH)
    // We'll treat world units as pixels relative to camera later via view matrix.
    auto push = [&](float px, float py){
        vertexData.push_back(px); vertexData.push_back(py);
        vertexData.push_back(r); vertexData.push_back(g);
        vertexData.push_back(b); vertexData.push_back(a);
    };

    // Triangle 1
    push(x - hw, y - hh);
    push(x + hw, y - hh);
    push(x + hw, y + hh);
    // Triangle 2
    push(x - hw, y - hh);
    push(x + hw, y + hh);
    push(x - hw, y + hh);
}

void Renderer2D::flush() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexData.size()*sizeof(float), vertexData.data());
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexData.size()/6));
    glBindVertexArray(0);
}
