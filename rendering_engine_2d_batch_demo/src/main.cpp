
#include "Renderer2D.hpp"
#include "Shader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <cstring>

static void glfw_error_callback(int code, const char* desc) {
    std::cerr << "GLFW error " << code << ": " << desc << std::endl;
}

int main(int argc, char** argv) {
    int quadCount = 5000;
    bool animate = true;
    for (int i = 1; i < argc; ++i) {
        if (std::strncmp(argv[i], "--quads=", 8) == 0) {
            quadCount = std::max(1, std::atoi(argv[i] + 8));
        } else if (std::strcmp(argv[i], "--no-anim") == 0) {
            animate = false;
        }
    }

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "2D Batch Renderer Demo", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    glViewport(0, 0, 1280, 720);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("shaders/quad.vert", "shaders/quad.frag");
    Renderer2D renderer(100000); // max vertices in batch
    renderer.setViewSize(1280.0f, 720.0f);

    // Generate a grid of quads
    std::vector<Quad> quads;
    quads.reserve(quadCount);
    int cols = static_cast<int>(std::sqrt(quadCount));
    int rows = (quadCount + cols - 1) / cols;
    float spacing = 18.0f;
    float startX = - (cols * spacing) * 0.5f;
    float startY = - (rows * spacing) * 0.5f;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if ((int)quads.size() >= quadCount) break;
            Quad q;
            q.pos[0] = startX + c * spacing;
            q.pos[1] = startY + r * spacing;
            q.size[0] = 14.0f;
            q.size[1] = 14.0f;
            float t = (float)quads.size() / (float)quadCount;
            q.color[0] = 0.2f + 0.8f * t;
            q.color[1] = 0.7f * (1.0f - t);
            q.color[2] = 0.9f;
            q.color[3] = 1.0f;
            quads.push_back(q);
        }
    }

    auto last = std::chrono::high_resolution_clock::now();
    float timeAcc = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        auto now = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float>(now - last).count();
        last = now;

        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, 1);

        // simple camera pan
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)  renderer.camera.x -= 200.0f * dt;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) renderer.camera.x += 200.0f * dt;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)  renderer.camera.y -= 200.0f * dt;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)    renderer.camera.y += 200.0f * dt;

        if (animate) timeAcc += dt;

        glClearColor(0.06f, 0.07f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        shader.setMat4("uProj", renderer.getProjection());
        shader.setMat4("uView", renderer.getView());

        renderer.begin();
        // animate in a sinusoidal wave for some quads
        for (size_t i = 0; i < quads.size(); ++i) {
            Quad q = quads[i];
            if (animate) {
                q.pos[1] += std::sin((float)i * 0.05f + timeAcc * 2.0f) * 4.0f;
            }
            renderer.pushQuad(q);
        }
        renderer.flush();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
