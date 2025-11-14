#include "../common/opengl_setup.h"

/*
 * Activity 2: Clipping
 * Purpose: Demonstrate viewport clipping and scissor test
 * TODO: Implement Cohen-Sutherland or other clipping algorithms
 */

void runActivity2() {
    // Initialize OpenGL window
    GLFWwindow* window = initializeOpenGL("Activity 2: Clipping", 800, 600);
    if (!window) return;

    // Set clear color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Vertex data for a line that will be clipped
    float vertices[] = {
        // Line 1: will be partially clipped
        -0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // red
         0.9f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,

        // Line 2: completely inside clip region
        -0.3f, -0.3f, 0.0f,  0.0f, 1.0f, 0.0f,  // green
         0.3f,  0.3f, 0.0f,  0.0f, 1.0f, 0.0f,

        // Rectangle representing clip region
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // blue
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
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

    // Enable line width for better visibility
    glLineWidth(2.0f);

    printf("Activity 2: Clipping\n");
    printf("TODO: Implement clipping algorithms (Cohen-Sutherland, Liang-Barsky, etc.)\n");
    printf("Current: Shows lines and clip region boundaries\n");
    printf("Press ESC to close.\n");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Draw lines
        glDrawArrays(GL_LINES, 0, 4);

        // Draw clip region boundary
        glDrawArrays(GL_LINE_LOOP, 4, 4);

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
