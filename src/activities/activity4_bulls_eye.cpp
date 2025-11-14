#include "../common/opengl_setup.h"
#include <cmath>
#include <vector>

/*
 * Activity 4: Bull's Eye Target
 * Purpose: Draw concentric circles forming a target pattern
 * Demonstrates circle drawing algorithms and filled shapes
 */

namespace activity4 {
const float PI = 3.14159265359f;

// Generate vertices for a filled circle
std::vector<float> generateCircle(float centerX, float centerY, float radius,
                                   float r, float g, float b, int segments) {
    std::vector<float> vertices;

    // Center vertex
    vertices.push_back(centerX);
    vertices.push_back(centerY);
    vertices.push_back(0.0f);
    vertices.push_back(r);
    vertices.push_back(g);
    vertices.push_back(b);

    // Generate circle vertices
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * float(i) / float(segments);
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
        vertices.push_back(r);
        vertices.push_back(g);
        vertices.push_back(b);
    }

    return vertices;
}
} // namespace activity4

void runActivity4() {
    using namespace activity4;
    // Initialize OpenGL window
    GLFWwindow* window = initializeOpenGL("Activity 4: Bull's Eye Target", 800, 800);
    if (!window) return;

    // Set clear color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Generate bull's eye circles (from largest to smallest)
    std::vector<float> allVertices;

    // Ring 1: Outer red ring
    auto ring1 = generateCircle(0.0f, 0.0f, 0.8f, 1.0f, 0.0f, 0.0f, 50);
    allVertices.insert(allVertices.end(), ring1.begin(), ring1.end());

    // Ring 2: White ring
    auto ring2 = generateCircle(0.0f, 0.0f, 0.6f, 1.0f, 1.0f, 1.0f, 50);
    allVertices.insert(allVertices.end(), ring2.begin(), ring2.end());

    // Ring 3: Red ring
    auto ring3 = generateCircle(0.0f, 0.0f, 0.4f, 1.0f, 0.0f, 0.0f, 50);
    allVertices.insert(allVertices.end(), ring3.begin(), ring3.end());

    // Ring 4: White ring
    auto ring4 = generateCircle(0.0f, 0.0f, 0.2f, 1.0f, 1.0f, 1.0f, 50);
    allVertices.insert(allVertices.end(), ring4.begin(), ring4.end());

    // Ring 5: Center red circle
    auto ring5 = generateCircle(0.0f, 0.0f, 0.08f, 1.0f, 0.0f, 0.0f, 50);
    allVertices.insert(allVertices.end(), ring5.begin(), ring5.end());

    // Create and bind VAO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(float),
                 allVertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Create shader program
    unsigned int shaderProgram = createShaderProgram(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);

    printf("Activity 4: Bull's Eye Target\n");
    printf("Displaying concentric circles forming a target pattern\n");
    printf("TODO: Add scoring zones, animations, or interactive features\n");
    printf("Press ESC to close.\n");

    // Calculate vertices per circle
    int segments = 50;
    int verticesPerCircle = segments + 2; // center + perimeter vertices

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Draw each circle as a triangle fan
        for (int i = 0; i < 5; i++) {
            glDrawArrays(GL_TRIANGLE_FAN, i * verticesPerCircle, verticesPerCircle);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}

#ifndef MAIN_DISPATCHER
int main() {
    runActivity4();
    return 0;
}
#endif
