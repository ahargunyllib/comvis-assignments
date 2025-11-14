#include "../common/opengl_setup.h"
#include <cmath>

/*
 * Activity 3: Color Interpolation
 * Purpose: Demonstrate color interpolation across shapes
 * Shows smooth color gradients using vertex colors
 */

void runActivity3() {
    // Initialize OpenGL window
    GLFWwindow* window = initializeOpenGL("Activity 3: Color Interpolation", 800, 600);
    if (!window) return;

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Vertex data: Two triangles forming a quad with different colors at each corner
    float vertices[] = {
        // First triangle
        // positions         // colors (RGB gradient)
        -0.8f, -0.6f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom left: red
         0.8f, -0.6f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right: green
        -0.8f,  0.6f, 0.0f,  0.0f, 0.0f, 1.0f,  // top left: blue

        // Second triangle
         0.8f, -0.6f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right: green
         0.8f,  0.6f, 0.0f,  1.0f, 1.0f, 0.0f,  // top right: yellow
        -0.8f,  0.6f, 0.0f,  0.0f, 0.0f, 1.0f   // top left: blue
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

    // Create shader program
    unsigned int shaderProgram = createShaderProgram(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);

    printf("Activity 3: Color Interpolation\n");
    printf("Demonstrating smooth color gradients across surfaces\n");
    printf("Colors are interpolated between vertices using rasterization\n");
    printf("Press ESC to close.\n");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Draw the quad (two triangles)
        glDrawArrays(GL_TRIANGLES, 0, 6);

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
