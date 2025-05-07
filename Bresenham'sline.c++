#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Start and End Points
int X1, Y1, X2, Y2;
bool firstClick = true;

// Line Style: 0 = Simple, 1 = Dotted, 2 = Dashed, 3 = Solid
int lineStyle = 0;

// Return sign of a number
int sign(int a) {
    return (a > 0) - (a < 0);
}

// Function to draw Bresenham line based on style
void drawBresenhamLine(int style) {
    int dx = abs(X2 - X1);
    int dy = abs(Y2 - Y1);
    int s1 = sign(X2 - X1);
    int s2 = sign(Y2 - Y1);

    bool interchange = false;
    if (dy > dx) {
        swap(dx, dy);
        interchange = true;
    }

    int g = 2 * dy - dx;
    int x = X1;
    int y = Y1;

    int count = 0;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (int i = 0; i <= dx; i++) {
        // Handle Line Style
        bool draw = false;
        switch (style) {
            case 0: draw = true; break;                        // Simple (default)
            case 1: draw = (count % 2 == 0); break;            // Dotted
            case 2: draw = (count % 8 < 5); break;             // Dashed (5 on, 3 off)
            case 3: draw = true; break;                        // Solid
        }

        if (draw) glVertex2i(x, y);

        while (g >= 0) {
            if (interchange)
                x += s1;
            else
                y += s2;
            g -= 2 * dx;
        }

        if (interchange)
            y += s2;
        else
            x += s1;
        g += 2 * dy;

        count++;
    }
    glEnd();

    // Draw Axis
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2i(320, 0);
        glVertex2i(320, 480);
        glVertex2i(0, 240);
        glVertex2i(640, 240);
    glEnd();

    glFlush();
}

// Mouse click handler
void mouseHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (firstClick) {
            X1 = x;
            Y1 = 480 - y;
            firstClick = false;
        } else {
            X2 = x;
            Y2 = 480 - y;
            firstClick = true;
            glutPostRedisplay();
        }
    }
}

// Keyboard handler to switch line styles
void keyboardHandler(unsigned char key, int x, int y) {
    switch (key) {
        case '0': lineStyle = 0; break; // Simple
        case '1': lineStyle = 1; break; // Dotted
        case '2': lineStyle = 2; break; // Dashed
        case '3': lineStyle = 3; break; // Solid
    }
    glutPostRedisplay();
}

// Display callback
void display() {
    drawBresenhamLine(lineStyle);
}

// Initialization
void Init() {
    glClearColor(0.0, 1.0, 0.0, 0.0);  // Background green
    glColor3f(0.0, 0.0, 0.0);          // Drawing color black
    gluOrtho2D(0, 640, 0, 480);        // Set coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Styles with Mouse");

    Init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseHandler);
    glutKeyboardFunc(keyboardHandler);
    glutMainLoop();
    return 0;
}
