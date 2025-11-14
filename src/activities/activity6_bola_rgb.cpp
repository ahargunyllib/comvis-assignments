#include "../common/opengl_setup.h"
#include <cmath>
#include <vector>

/*
 * Activity 6: Bola Merah Kuning Biru (Red Yellow Blue Balls)
 * Purpose: Display three colored spheres/circles
 * TODO: Add 3D sphere rendering, lighting, and animation
 */

namespace activity6 {
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
} // namespace activity6

void runActivity6() {
    using namespace activity6;
    // Initialize OpenGL window
    GLFWwindow* window = initializeOpenGL("Activity 6: Bola Merah Kuning Biru", 900, 400);
    if (!window) return;

    // Set clear color
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    // Generate three circles
    std::vector<float> allVertices;

    // Red ball (left)
    auto redBall = generateCircle(-0.6f, 0.0f, 0.3f, 1.0f, 0.0f, 0.0f, 50);
    allVertices.insert(allVertices.end(), redBall.begin(), redBall.end());

    // Yellow ball (center)
    auto yellowBall = generateCircle(0.0f, 0.0f, 0.3f, 1.0f, 1.0f, 0.0f, 50);
    allVertices.insert(allVertices.end(), yellowBall.begin(), yellowBall.end());

    // Blue ball (right)
    auto blueBall = generateCircle(0.6f, 0.0f, 0.3f, 0.0f, 0.0f, 1.0f, 50);
    allVertices.insert(allVertices.end(), blueBall.begin(), blueBall.end());

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

    printf("Activity 6: Bola Merah Kuning Biru\n");
    printf("Displaying three colored balls: Red, Yellow, Blue\n");
    printf("TODO: Add 3D sphere rendering, shading, or animations\n");
    printf("Press ESC to close.\n");

    // Calculate vertices per circle
    int segments = 50;
    int verticesPerCircle = segments + 2;

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Draw three balls
        for (int i = 0; i < 3; i++) {
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
    runActivity6();
    return 0;
}
#endif
