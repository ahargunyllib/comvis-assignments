#include "../common/opengl_setup.h"

/*
 * Activity 2: Clipping
 * Purpose: Demonstrate viewport clipping with a triangle
 * Based on: Experiment 2.6 - Triangle for dramatic clipping illustration
 * TODO: Implement Cohen-Sutherland or other clipping algorithms
 */

void runActivity2() {
    // Initialize OpenGL window
    GLFWwindow* window = initializeOpenGL("square.cpp", 500, 500);
    if (!window) return;

    // Set clear color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Vertex data: Right triangle in 0-100 coordinate space
    // Using only 3 vertices for better clipping demonstration
    // Format: position (x, y, z)
    float vertices[] = {
        // Triangle vertices (Experiment 2.6)
        30.0f, 30.0f, 0.0f,  // Bottom-left
        70.0f, 30.0f, 0.0f,  // Bottom-right
        70.0f, 70.0f, 0.0f   // Top-right
    };

    // Create and bind VAO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute (only position, no color per vertex)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create custom shaders with orthographic projection
    const char* vertexShaderSource = "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "   gl_Position = projection * vec4(aPos, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 410 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(0.0, 0.0, 0.0, 1.0);  // Black color\n"
        "}\0";

    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Create orthographic projection matrix (0-100 coordinate space)
    // This is equivalent to glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0)
    float projectionMatrix[16] = {
        2.0f/100.0f,  0.0f,          0.0f,  0.0f,
        0.0f,         2.0f/100.0f,   0.0f,  0.0f,
        0.0f,         0.0f,         -1.0f,  0.0f,
       -1.0f,        -1.0f,          0.0f,  1.0f
    };

    // Set the projection matrix uniform
    glUseProgram(shaderProgram);
    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projectionMatrix);

    printf("Activity 2: Clipping\n");
    printf("A black right triangle should appear on white background.\n");
    printf("Triangle vertices: (30,30), (70,30), (70,70)\n");
    printf("Simpler geometry makes clipping behavior more obvious.\n");
    printf("TODO: Implement Cohen-Sutherland or Liang-Barsky clipping algorithms\n");
    printf("Press ESC to close.\n");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen to white
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw 3 vertices (1 triangle)

        // Swap buffers and poll events
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
    runActivity2();
    return 0;
}
#endif
