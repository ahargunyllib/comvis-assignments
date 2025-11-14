#include "../common/opengl_setup.h"
#include <cmath>
#include <vector>

/*
 * Activity 4: Circular Annuluses (Bull's Eye)
 * Purpose: Demonstrate three different techniques for drawing circular annuluses
 * Based on: circularAnnuluses.cpp by Sumanta Guha
 *
 * Three annuluses demonstrating different techniques:
 * 1. Upper left: Overwriting technique (white disc over red disc)
 * 2. Upper right: Depth testing (multi-colored bull's eye with depth testing)
 * 3. Lower: True ring using triangle strip (toggleable wireframe)
 */

#define N 40.0  // Number of vertices on the boundary of the disc

// Use system M_PI from <cmath>
#ifndef M_PI
#endif

// Global state
static bool isWire = false;  // Wireframe toggle for lower annulus

// Vertex generation functions
std::vector<float> generateDiscVertices(float radius, float centerX, float centerY, float centerZ) {
    std::vector<float> vertices;

    // Center vertex
    vertices.push_back(centerX);
    vertices.push_back(centerY);
    vertices.push_back(centerZ);

    // Boundary vertices (triangle fan)
    for (int i = 0; i <= N; ++i) {
        float t = 2.0f * M_PI * i / N;
        vertices.push_back(centerX + cos(t) * radius);
        vertices.push_back(centerY + sin(t) * radius);
        vertices.push_back(centerZ);
    }

    return vertices;
}

std::vector<float> generateRingVertices(float innerRadius, float outerRadius,
                                        float centerX, float centerY, float centerZ) {
    std::vector<float> vertices;

    // Triangle strip: alternating inner and outer vertices
    for (int i = 0; i <= N; ++i) {
        float angle = 2.0f * M_PI * i / N;

        // Inner vertex
        vertices.push_back(centerX + cos(angle) * innerRadius);
        vertices.push_back(centerY + sin(angle) * innerRadius);
        vertices.push_back(centerZ);

        // Outer vertex
        vertices.push_back(centerX + cos(angle) * outerRadius);
        vertices.push_back(centerY + sin(angle) * outerRadius);
        vertices.push_back(centerZ);
    }

    return vertices;
}

// Keyboard callback for wireframe toggle
void activity4KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;  // Unused parameter
    (void)mods;      // Unused parameter
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_SPACE) {
            isWire = !isWire;
            printf("Wireframe mode: %s\n", isWire ? "ON" : "OFF");
        } else if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

void runActivity4() {
    // Initialize OpenGL window
    GLFWwindow* window = initializeOpenGL("Activity 4: Circular Annuluses", 500, 500);
    if (!window) return;

    // Set keyboard callback (override default to handle SPACE)
    glfwSetKeyCallback(window, activity4KeyCallback);

    // Set clear color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Enable depth testing capability (will enable/disable during rendering)
    glEnable(GL_DEPTH_TEST);

    // Generate vertex data for all geometry
    // Upper left annulus (overwriting technique)
    auto upperLeftRed = generateDiscVertices(20.0f, 25.0f, 75.0f, 0.0f);
    auto upperLeftWhite = generateDiscVertices(10.0f, 25.0f, 75.0f, 0.0f);

    // Upper right multi-colored bull's eye (depth testing technique)
    // 5 concentric discs with different colors and z-values
    auto bullsEyeGreen = generateDiscVertices(20.0f, 75.0f, 75.0f, 0.0f);    // Outermost - Green
    auto bullsEyeRed = generateDiscVertices(16.0f, 75.0f, 75.0f, 0.1f);      // Red
    auto bullsEyeBlue = generateDiscVertices(12.0f, 75.0f, 75.0f, 0.2f);     // Blue
    auto bullsEyeYellow = generateDiscVertices(8.0f, 75.0f, 75.0f, 0.3f);    // Yellow
    auto bullsEyePurple = generateDiscVertices(4.0f, 75.0f, 75.0f, 0.4f);    // Center - Purple

    // Lower annulus (true ring with triangle strip)
    auto lowerRing = generateRingVertices(10.0f, 20.0f, 50.0f, 30.0f, 0.0f);

    // Create VAO/VBO for each geometry (2 for upper left + 5 for bull's eye + 1 for lower = 8 total)
    unsigned int VAOs[8], VBOs[8];
    glGenVertexArrays(8, VAOs);
    glGenBuffers(8, VBOs);

    // Helper lambda to setup VAO/VBO
    auto setupGeometry = [](unsigned int VAO, unsigned int VBO, const std::vector<float>& vertices) {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    };

    // Setup all geometry
    setupGeometry(VAOs[0], VBOs[0], upperLeftRed);
    setupGeometry(VAOs[1], VBOs[1], upperLeftWhite);
    setupGeometry(VAOs[2], VBOs[2], bullsEyeGreen);
    setupGeometry(VAOs[3], VBOs[3], bullsEyeRed);
    setupGeometry(VAOs[4], VBOs[4], bullsEyeBlue);
    setupGeometry(VAOs[5], VBOs[5], bullsEyeYellow);
    setupGeometry(VAOs[6], VBOs[6], bullsEyePurple);
    setupGeometry(VAOs[7], VBOs[7], lowerRing);

    // Create shaders with uniform color
    const char* vertexShaderSource = "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "   gl_Position = projection * vec4(aPos, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 410 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 color;\n"
        "void main() {\n"
        "   FragColor = color;\n"
        "}\0";

    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Create orthographic projection matrix (0-100 coordinate space)
    float projectionMatrix[16] = {
        2.0f/100.0f,  0.0f,          0.0f,  0.0f,
        0.0f,         2.0f/100.0f,   0.0f,  0.0f,
        0.0f,         0.0f,         -1.0f,  0.0f,
       -1.0f,        -1.0f,          0.0f,  1.0f
    };

    // Set uniforms
    glUseProgram(shaderProgram);
    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projectionMatrix);

    // Store vertex counts
    int discVertexCount = (int)upperLeftRed.size() / 3;
    int ringVertexCount = (int)lowerRing.size() / 3;

    printf("\n=== Activity 4: Circular Annuluses ===\n");
    printf("Three techniques for drawing annuluses (ring shapes):\n\n");
    printf("1. UPPER LEFT (25, 75) - 'Overwritten' Technique:\n");
    printf("   - Red disc (radius 20) at z=0\n");
    printf("   - White disc (radius 10) painted over it\n");
    printf("   - Simple but imprecise (overlapping geometry)\n\n");
    printf("2. UPPER RIGHT (75, 75) - 'Floating' Technique:\n");
    printf("   - Multi-colored bull's eye with depth testing\n");
    printf("   - 5 concentric discs: Green -> Red -> Blue -> Yellow -> Purple\n");
    printf("   - Each at different z-depth (0.0 to 0.4)\n");
    printf("   - Demonstrates layered rendering\n\n");
    printf("3. LOWER CENTER (50, 30) - 'The Real Deal' Technique:\n");
    printf("   - True ring using GL_TRIANGLE_STRIP\n");
    printf("   - Inner radius 10, outer radius 20\n");
    printf("   - Proper geometry, efficient rendering\n\n");
    printf("Controls:\n");
    printf("  SPACE - Toggle wireframe for lower annulus\n");
    printf("  ESC   - Close window\n\n");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear screen and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // ===== UPPER LEFT: Overwriting technique (no depth test) =====
        glDisable(GL_DEPTH_TEST);

        // Red disc
        glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);  // Red
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, discVertexCount);

        // White disc (overwrites red)
        glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);  // White
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, discVertexCount);

        // ===== UPPER RIGHT: Multi-colored bull's eye with depth testing =====
        glEnable(GL_DEPTH_TEST);

        // Green disc (outermost) at z=0
        glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);  // Green
        glBindVertexArray(VAOs[2]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, discVertexCount);

        // Red disc at z=0.1
        glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);  // Red
        glBindVertexArray(VAOs[3]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, discVertexCount);

        // Blue disc at z=0.2
        glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);  // Blue
        glBindVertexArray(VAOs[4]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, discVertexCount);

        // Yellow disc at z=0.3
        glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);  // Yellow
        glBindVertexArray(VAOs[5]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, discVertexCount);

        // Purple disc (center) at z=0.4
        glUniform4f(colorLoc, 0.6f, 0.0f, 0.8f, 1.0f);  // Purple/Magenta
        glBindVertexArray(VAOs[6]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, discVertexCount);

        glDisable(GL_DEPTH_TEST);

        // ===== LOWER: True ring with triangle strip =====
        // Set polygon mode based on wireframe toggle
        if (isWire) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);  // Red
        glBindVertexArray(VAOs[7]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, ringVertexCount);

        // Reset polygon mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(8, VAOs);
    glDeleteBuffers(8, VBOs);
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
