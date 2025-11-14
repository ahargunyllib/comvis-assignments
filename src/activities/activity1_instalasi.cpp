#include "../common/opengl_setup.h"

/*
 * Activity 1: Instalasi (Installation)
 * Purpose: Verify OpenGL installation and display a basic triangle
 */

void runActivity1() {
    // Initialize OpenGL window
    GLFWwindow* window = initializeOpenGL("Activity 1: Instalasi", 640, 480);
    if (!window) return;

    // Set clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Vertex data: position (x, y, z) and color (r, g, b)
    float vertices[] = {
        // positions         // colors
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom left (red)
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right (green)
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top (blue)
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

    printf("Activity 1: Installation Test\n");
    printf("A colored triangle should appear on screen.\n");
    printf("Press ESC to close.\n");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
