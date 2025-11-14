#include "../common/opengl_setup.h"
#include <cmath>
#include <vector>

/*
 * Activity 8: Undistorted Cray 2
 * Purpose: Demonstrate distortion correction or grid rendering
 * TODO: Implement barrel/pincushion distortion correction algorithms
 */

void runActivity8() {
    // Initialize OpenGL window
    GLFWwindow* window = initializeOpenGL("Activity 8: Undistorted Cray 2", 800, 800);
    if (!window) return;

    // Set clear color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Generate a grid of vertices
    const int gridSize = 20;
    std::vector<float> vertices;

    // Create horizontal lines
    for (int i = 0; i <= gridSize; i++) {
        float y = -1.0f + (2.0f * i / gridSize);

        // Line start
        vertices.push_back(-1.0f);
        vertices.push_back(y);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.8f);
        vertices.push_back(1.0f);

        // Line end
        vertices.push_back(1.0f);
        vertices.push_back(y);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.8f);
        vertices.push_back(1.0f);
    }

    // Create vertical lines
    for (int i = 0; i <= gridSize; i++) {
        float x = -1.0f + (2.0f * i / gridSize);

        // Line start
        vertices.push_back(x);
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.8f);
        vertices.push_back(1.0f);

        // Line end
        vertices.push_back(x);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.8f);
        vertices.push_back(1.0f);
    }

    // Create reference shapes to visualize distortion
    // Square in the center
    float square[] = {
        -0.3f, -0.3f, 0.0f,  1.0f, 0.5f, 0.0f,
         0.3f, -0.3f, 0.0f,  1.0f, 0.5f, 0.0f,
         0.3f,  0.3f, 0.0f,  1.0f, 0.5f, 0.0f,
        -0.3f,  0.3f, 0.0f,  1.0f, 0.5f, 0.0f
    };

    for (int i = 0; i < 24; i++) {
        vertices.push_back(square[i]);
    }

    // Create and bind VAO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Create shader program
    unsigned int shaderProgram = createShaderProgram(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);

    glLineWidth(1.0f);

    printf("Activity 8: Undistorted Cray 2\n");
    printf("Displaying an undistorted grid for reference\n");
    printf("TODO: Add distortion effects and correction algorithms\n");
    printf("      - Barrel distortion\n");
    printf("      - Pincushion distortion\n");
    printf("      - Camera lens distortion correction\n");
    printf("Press ESC to close.\n");

    // Calculate line count
    int horizontalLines = (gridSize + 1) * 2;
    int verticalLines = (gridSize + 1) * 2;
    int totalLineVertices = horizontalLines + verticalLines;

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Draw grid lines
        glDrawArrays(GL_LINES, 0, totalLineVertices);

        // Draw reference square
        glLineWidth(2.0f);
        glDrawArrays(GL_LINE_LOOP, totalLineVertices, 4);
        glLineWidth(1.0f);

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
    runActivity8();
    return 0;
}
#endif
