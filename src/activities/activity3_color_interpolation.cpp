#include "../common/opengl_setup.h"

/*
 * Activity 3: Color Interpolation
 * Purpose: Demonstrate bilinear color interpolation across a square
 * Based on: Experiment 2.7 - Four-corner color gradient
 * Shows smooth color gradients using vertex colors and GPU rasterization
 */

void runActivity3() {
    // Initialize OpenGL window (500x500 square)
    GLFWwindow* window = initializeOpenGL("square.cpp", 500, 500);
    if (!window) return;

    // Set clear color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Vertex data: Square with different color at each corner
    // Format: position (x, y, z), color (r, g, b)
    float vertices[] = {
        // First triangle (bottom-left, bottom-right, top-left)
        20.0f, 20.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom-left: Red
        80.0f, 20.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom-right: Green
        20.0f, 80.0f, 0.0f,  1.0f, 1.0f, 0.0f,  // Top-left: Yellow

        // Second triangle (bottom-right, top-right, top-left)
        80.0f, 20.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom-right: Green
        80.0f, 80.0f, 0.0f,  0.0f, 0.0f, 1.0f,  // Top-right: Blue
        20.0f, 80.0f, 0.0f,  1.0f, 1.0f, 0.0f   // Top-left: Yellow
    };

    // Create and bind VAO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Create shaders with orthographic projection
    const char* vertexShaderSource = "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "uniform mat4 projection;\n"
        "out vec3 vertexColor;\n"
        "void main() {\n"
        "   gl_Position = projection * vec4(aPos, 1.0);\n"
        "   vertexColor = aColor;\n"
        "}\0";

    const char* fragmentShaderSource = "#version 410 core\n"
        "in vec3 vertexColor;\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(vertexColor, 1.0);\n"
        "}\0";

    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Create orthographic projection matrix (0-100 coordinate space)
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

    printf("Activity 3: Color Interpolation (Experiment 2.7)\n");
    printf("Demonstrating bilinear color interpolation across a square.\n");
    printf("Corner colors: Red (BL), Green (BR), Yellow (TL), Blue (TR)\n");
    printf("GPU automatically interpolates colors between vertices.\n");
    printf("Press ESC to close.\n");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen to white
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the square with interpolated colors
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
    runActivity3();
    return 0;
}
#endif
