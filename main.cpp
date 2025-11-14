#define MAIN_DISPATCHER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Forward declarations for activity functions
void runActivity1();
void runActivity2();
void runActivity3();
void runActivity4();
void runActivity6();
void runActivity7();
void runActivity8();

void printUsage(const char* programName) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║        Computer Vision Assignments - Activity Launcher     ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Usage: %s <activity_number>\n\n", programName);
    printf("Available activities:\n");
    printf("  1  - Instalasi (Installation Test)\n");
    printf("       Verify OpenGL installation with a colored triangle\n\n");
    printf("  2  - Clipping\n");
    printf("       Demonstrate viewport clipping and scissor test\n\n");
    printf("  3  - Color Interpolation\n");
    printf("       Show smooth color gradients across surfaces\n\n");
    printf("  4  - Bull's Eye Target\n");
    printf("       Draw concentric circles forming a target pattern\n\n");
    printf("  6  - Bola Merah Kuning Biru (Red Yellow Blue Balls)\n");
    printf("       Display three colored spheres/circles\n\n");
    printf("  7  - Satelite Duo (Satellite Duo)\n");
    printf("       Simulate orbital motion with two satellites\n\n");
    printf("  8  - Undistorted Cray 2\n");
    printf("       Demonstrate distortion correction with grid rendering\n\n");
    printf("Examples:\n");
    printf("  %s 1    # Run activity 1 (Instalasi)\n", programName);
    printf("  %s 4    # Run activity 4 (Bull's Eye)\n", programName);
    printf("\n");
}

int main(int argc, char* argv[]) {
    // Check if activity number is provided
    if (argc != 2) {
        printf("Error: Missing activity number\n");
        printUsage(argv[0]);
        return 1;
    }

    // Parse activity number
    int activityNum = atoi(argv[1]);

    // Launch the requested activity
    switch (activityNum) {
        case 1:
            printf("Launching Activity 1: Instalasi\n");
            printf("═══════════════════════════════════════\n\n");
            runActivity1();
            break;

        case 2:
            printf("Launching Activity 2: Clipping\n");
            printf("═══════════════════════════════════════\n\n");
            runActivity2();
            break;

        case 3:
            printf("Launching Activity 3: Color Interpolation\n");
            printf("═══════════════════════════════════════\n\n");
            runActivity3();
            break;

        case 4:
            printf("Launching Activity 4: Bull's Eye Target\n");
            printf("═══════════════════════════════════════\n\n");
            runActivity4();
            break;

        case 6:
            printf("Launching Activity 6: Bola Merah Kuning Biru\n");
            printf("═══════════════════════════════════════\n\n");
            runActivity6();
            break;

        case 7:
            printf("Launching Activity 7: Satelite Duo\n");
            printf("═══════════════════════════════════════\n\n");
            runActivity7();
            break;

        case 8:
            printf("Launching Activity 8: Undistorted Cray 2\n");
            printf("═══════════════════════════════════════\n\n");
            runActivity8();
            break;

        default:
            printf("Error: Invalid activity number '%d'\n", activityNum);
            printf("Note: Activity 5 is not available in this assignment set\n\n");
            printUsage(argv[0]);
            return 1;
    }

    return 0;
}

// Include activity implementations
#include "src/activities/activity1_instalasi.cpp"
#include "src/activities/activity2_clipping.cpp"
#include "src/activities/activity3_color_interpolation.cpp"
#include "src/activities/activity4_bulls_eye.cpp"
#include "src/activities/activity6_bola_rgb.cpp"
#include "src/activities/activity7_satelite_duo.cpp"
#include "src/activities/activity8_undistorted_cray.cpp"
