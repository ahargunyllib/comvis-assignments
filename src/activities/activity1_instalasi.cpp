#include "../common/opengl_setup.h"

/*
 * Activity 1: Instalasi (Installation)
 * Purpose: Verify OpenGL installation and display a black square
 * Based on: square.cpp by Sumanta Guha
 */

void runActivity1() {
    // Initialize OpenGL window (500x500 to match original example)
    GLFWwindow* window = initializeOpenGL("square.cpp", 500, 500);
    if (!window) return;

    // Set clear color to white (matching original example)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Vertex data: Square from (20,20) to (80,80) in 0-100 coordinate space
    // We draw it as 2 triangles (6 vertices total)
    // Format: position (x, y, z)
    float vertices[] = {
        // First triangle (bottom-left, bottom-right, top-right)
        20.0f, 20.0f, 0.0f,
        80.0f, 20.0f, 0.0f,
        80.0f, 80.0f, 0.0f,

        // Second triangle (bottom-left, top-right, top-left)
        20.0f, 20.0f, 0.0f,
        80.0f, 80.0f, 0.0f,
        20.0f, 80.0f, 0.0f
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

    printf("Activity 1: Installation Test\n");
    printf("A black square should appear on white background.\n");
    printf("Square position: (20, 20) to (80, 80) in 100x100 coordinate space\n");
    printf("Press ESC to close.\n");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen to white
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the square
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);  // Draw 6 vertices (2 triangles)

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
    runActivity1();
    return 0;
}
#endif
