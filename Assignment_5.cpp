#include <freeglut.h>
#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>

float x_center = 0, y_center = 0;  // Center of the ellipse
float rx = 100;                    // Default x-radius (horizontal radius)
float ry = 100;                     // Default y-radius (vertical radius)
bool animate = true;               // Enable animation

// Delay function for animation
void delay(unsigned int microseconds) {
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}

// Function to plot a pixel at (x, y)
void putPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x_center + x, y_center + y);
    glEnd();
    glFlush();
}

// Function to draw the ellipse using a single equation (midpoint algorithm)
void drawEllipse() {
    float x = 0;
    float y = ry;

    float rxSq = rx * rx;
    float rySq = ry * ry;

    float p = rySq - (rxSq * ry) + (0.25 * rxSq);  // Initial decision parameter

    while (2 * rySq * x <= 2 * rxSq * y) {
        // Plot in all 4 quadrants
        putPixel(x, y);     // Q1
        putPixel(-x, y);    // Q2
        putPixel(-x, -y);   // Q3
        putPixel(x, -y);    // Q4

        if (animate) {
            delay(20000);   // Animation delay (20ms)
        }

        x++;  // Increment x for region 1
        if (p < 0) {
            p += (2 * rySq * x) + rySq;  // Update decision parameter for region 1
        }
        else {
            y--;  // Move down in y
            p += (2 * rySq * x) - (2 * rxSq * y) + rySq;  // Update decision parameter for region 1
        }
    }

    // Reset decision parameter for region 2
    p = rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq;

    while (y >= 0) {
        // Plot in all 4 quadrants
        putPixel(x, y);     // Q1
        putPixel(-x, y);    // Q2
        putPixel(-x, -y);   // Q3
        putPixel(x, -y);    // Q4

        if (animate) {
            delay(20000);   // Animation delay (20ms)
        }

        y--;  // Decrease y for region 2
        if (p > 0) {
            p -= (2 * rxSq * y) + rxSq;  // Update decision parameter for region 2
        }
        else {
            x++;  // Move forward in x
            p += (2 * rySq * x) - (2 * rxSq * y) + rxSq;  // Update decision parameter for region 2
        }
    }
}

// Display callback to clear and draw the ellipse
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawEllipse();  // Draw the ellipse
}

// Initialization for OpenGL settings
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background to white
    glColor3f(0.0, 0.0, 0.0);         // Set drawing color to black
    glPointSize(2.0);                 // Set point size to 2 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250); // Set coordinate system
}

// Main function to initialize the GLUT loop
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Midpoint Ellipse Algorithm - Simplified");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

