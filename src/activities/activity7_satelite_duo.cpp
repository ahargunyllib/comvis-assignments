#include "../common/opengl_setup.h"
#include <cmath>
#include <vector>

/*
 * Activity 7: Satelite Duo (Satellite Duo)
 * Purpose: Simulate orbital motion with two satellites
 * Demonstrates animation and circular motion
 */

namespace activity7 {
const float PI = 3.14159265359f;

// Generate vertices for a filled circle
std::vector<float> generateCircle(float centerX, float centerY, float radius,
                                   float r, float g, float b, int segments) {
    std::vector<float> vertices;

    vertices.push_back(centerX);
    vertices.push_back(centerY);
    vertices.push_back(0.0f);
    vertices.push_back(r);
    vertices.push_back(g);
    vertices.push_back(b);

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

// Generate vertices for an orbit path (circle outline)
std::vector<float> generateOrbitPath(float centerX, float centerY, float radius,
                                      float r, float g, float b, int segments) {
    std::vector<float> vertices;

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
} // namespace activity7

void runActivity7() {
    using namespace activity7;
    // Initialize OpenGL window
    GLFWwindow* window = initializeOpenGL("Activity 7: Satelite Duo", 800, 800);
    if (!window) return;

    // Set clear color
    glClearColor(0.05f, 0.05f, 0.15f, 1.0f);

    // Central planet vertices (static)
    auto planet = generateCircle(0.0f, 0.0f, 0.15f, 1.0f, 0.8f, 0.0f, 30);

    // Orbit paths
    auto orbit1Path = generateOrbitPath(0.0f, 0.0f, 0.5f, 0.3f, 0.3f, 0.4f, 100);
    auto orbit2Path = generateOrbitPath(0.0f, 0.0f, 0.7f, 0.3f, 0.3f, 0.4f, 100);

    // Create VAOs and VBOs for static objects
    unsigned int planetVAO, planetVBO;
    glGenVertexArrays(1, &planetVAO);
    glGenBuffers(1, &planetVBO);
    glBindVertexArray(planetVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planetVBO);
    glBufferData(GL_ARRAY_BUFFER, planet.size() * sizeof(float), planet.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // VAO for orbit paths
    unsigned int orbitVAO, orbitVBO;
    glGenVertexArrays(1, &orbitVAO);
    glGenBuffers(1, &orbitVBO);

    // VAO for satellites (dynamic)
    unsigned int satelliteVAO, satelliteVBO;
    glGenVertexArrays(1, &satelliteVAO);
    glGenBuffers(1, &satelliteVBO);

    // Create shader program
    unsigned int shaderProgram = createShaderProgram(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);

    glLineWidth(1.5f);

    printf("Activity 7: Satelite Duo\n");
    printf("Two satellites orbiting a central planet\n");
    printf("Satellite 1 (Cyan): Inner orbit, faster\n");
    printf("Satellite 2 (Magenta): Outer orbit, slower\n");
    printf("Press ESC to close.\n");

    float angle1 = 0.0f;
    float angle2 = 0.0f;
    float speed1 = 1.0f;
    float speed2 = 0.6f;

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Draw orbit paths
        glBindVertexArray(orbitVAO);
        glBindBuffer(GL_ARRAY_BUFFER, orbitVBO);

        // Orbit 1
        glBufferData(GL_ARRAY_BUFFER, orbit1Path.size() * sizeof(float), orbit1Path.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_LINE_LOOP, 0, orbit1Path.size() / 6);

        // Orbit 2
        glBufferData(GL_ARRAY_BUFFER, orbit2Path.size() * sizeof(float), orbit2Path.data(), GL_STATIC_DRAW);
        glDrawArrays(GL_LINE_LOOP, 0, orbit2Path.size() / 6);

        // Draw central planet
        glBindVertexArray(planetVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, planet.size() / 6);

        // Calculate satellite positions
        float sat1X = 0.5f * cos(angle1);
        float sat1Y = 0.5f * sin(angle1);
        auto satellite1 = generateCircle(sat1X, sat1Y, 0.05f, 0.0f, 1.0f, 1.0f, 30);

        float sat2X = 0.7f * cos(angle2);
        float sat2Y = 0.7f * sin(angle2);
        auto satellite2 = generateCircle(sat2X, sat2Y, 0.05f, 1.0f, 0.0f, 1.0f, 30);

        // Draw satellites
        glBindVertexArray(satelliteVAO);
        glBindBuffer(GL_ARRAY_BUFFER, satelliteVBO);

        glBufferData(GL_ARRAY_BUFFER, satellite1.size() * sizeof(float), satellite1.data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLE_FAN, 0, satellite1.size() / 6);

        glBufferData(GL_ARRAY_BUFFER, satellite2.size() * sizeof(float), satellite2.data(), GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_FAN, 0, satellite2.size() / 6);

        // Update angles
        angle1 += speed1 * 0.02f;
        angle2 += speed2 * 0.02f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &planetVAO);
    glDeleteBuffers(1, &planetVBO);
    glDeleteVertexArrays(1, &orbitVAO);
    glDeleteBuffers(1, &orbitVBO);
    glDeleteVertexArrays(1, &satelliteVAO);
    glDeleteBuffers(1, &satelliteVBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}

#ifndef MAIN_DISPATCHER
int main() {
    runActivity7();
    return 0;
}
#endif
