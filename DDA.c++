#include<iostream>
#include<math.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

using namespace std;

double X1, Y1, X2, Y2;
int lineStyle = 1; // 1: Simple, 2: Dotted, 3: Dashed, 4: Solid

void drawAxes() {
    glLineWidth(2);
    glBegin(GL_LINES);
    // Draw X-axis (centered)
    glVertex2i(0, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) / 2);
    // Draw Y-axis (centered)
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH) / 2, 0);
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT));

    // Draw quadrant lines (optional visualization)
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT));

    glVertex2i(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) / 2);

    glEnd();
}

void LineDDA(void) {
    double dx = (X2 - X1);
    double dy = (Y2 - Y1);
    double steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = X1;
    float y = Y1;

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glBegin(GL_POINTS);

    for (int k = 0; k <= steps; k++) {
        bool draw = false;

        // Handle line style
        switch (lineStyle) {
            case 1: // Simple
                draw = true;
                break;
            case 2: // Dotted
                draw = (k % 8 == 0); // Plot every 8th pixel
                break;
            case 3: // Dashed
                draw = ((k / 10) % 2 == 0); // 10 on, 10 off
                break;
            case 4: // Solid
                draw = true;
                break;
        }

        if (draw) {
            glVertex2d(x, y);
        }

        x += xInc;
        y += yInc;
    }

    glEnd();
    drawAxes(); // Draw coordinate axes
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1': lineStyle = 1; break; // Simple
        case '2': lineStyle = 2; break; // Dotted
        case '3': lineStyle = 3; break; // Dashed
        case '4': lineStyle = 4; break; // Solid
    }
    glutPostRedisplay(); // Refresh screen
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (X1 == 0 && Y1 == 0) {
            X1 = x - glutGet(GLUT_WINDOW_WIDTH) / 2;
            Y1 = glutGet(GLUT_WINDOW_HEIGHT) / 2 - y;
        } else {
            X2 = x - glutGet(GLUT_WINDOW_WIDTH) / 2;
            Y2 = glutGet(GLUT_WINDOW_HEIGHT) / 2 - y;
            glutPostRedisplay();
        }
    }
}

void Init() {
    glClearColor(0.0, 1.0, 0.0, 0);      // Green background
    glColor3f(0.0, 0.0, 0.0);            // Black drawing color
    gluOrtho2D(-320, 320, -240, 240);    // Set coordinate system (-320 to 320, -240 to 240)
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Line with Styles");
    Init();
    glutDisplayFunc(LineDDA);
    glutKeyboardFunc(keyboard); // Keyboard to change line style
    glutMouseFunc(mouse);       // Mouse to draw line
    glutMainLoop();

    return 0;
}




---------------------------------------------------------------------------------------------------------------------------


without mouse function


#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;

double X1, Y1, X2, Y2;
int lineStyle = 1; // 1: Simple, 2: Dotted, 3: Dashed, 4: Solid

void drawAxes() {
    glLineWidth(2);
    glBegin(GL_LINES);

    // X-axis
    glVertex2i(-320, 0);
    glVertex2i(320, 0);

    // Y-axis
    glVertex2i(0, -240);
    glVertex2i(0, 240);

    glEnd();
}

void LineDDA(void) {
    double dx = X2 - X1;
    double dy = Y2 - Y1;
    double steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = X1;
    float y = Y1;

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glBegin(GL_POINTS);

    for (int k = 0; k <= steps; k++) {
        bool draw = false;

        switch (lineStyle) {
            case 1: draw = true; break;                         // Simple
            case 2: draw = (k % 8 == 0); break;                 // Dotted
            case 3: draw = ((k / 10) % 2 == 0); break;          // Dashed
            case 4: draw = true; break;                         // Solid (same as simple here)
        }

        if (draw)
            glVertex2d(x, y);

        x += xInc;
        y += yInc;
    }

    glEnd();
    drawAxes(); // Draw coordinate axes
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1': lineStyle = 1; break;
        case '2': lineStyle = 2; break;
        case '3': lineStyle = 3; break;
        case '4': lineStyle = 4; break;
    }
    glutPostRedisplay();
}

void Init() {
    glClearColor(0.0, 1.0, 0.0, 0);       // Green background
    glColor3f(0.0, 0.0, 0.0);             // Black drawing color
    gluOrtho2D(-320, 320, -240, 240);     // Coordinate system centered at (0, 0)
}

int main(int argc, char **argv) {
    cout << "Enter first point (X1 Y1): ";
    cin >> X1 >> Y1;

    cout << "Enter second point (X2 Y2): ";
    cin >> X2 >> Y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line with Styles");
    Init();
    glutDisplayFunc(LineDDA);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
