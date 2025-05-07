#include <stdio.h>
#include <GL/glut.h>

// Function to plot all 8 symmetric points
void plot_circle_points(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

// Bresenham's Circle Drawing Algorithm
void bresenham_circle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;

    while (x <= y) {
        plot_circle_points(xc, yc, x, y);
        x++;
        if (p < 0) {
            p = p + 4 * x + 6;
        } else {
            y--;
            p = p + 4 * (x - y) + 10;
        }
    }
}

// Function to draw circles in all 4 quadrants
void draw_circles_all_quadrants() {
    glClear(GL_COLOR_BUFFER_BIT);

    int radius = 50;

    // Center at origin
    bresenham_circle(0, 0, radius);

    // 1st Quadrant (+x, +y)
    bresenham_circle(100, 100, radius);

    // 2nd Quadrant (-x, +y)
    bresenham_circle(-100, 100, radius);

    // 3rd Quadrant (-x, -y)
    bresenham_circle(-100, -100, radius);

    // 4th Quadrant (+x, -y)
    bresenham_circle(100, -100, radius);

    glFlush();
}

// Initialization
void Init() {
    glClearColor(1.0, 1.0, 1.0, 0); // white background
    glColor3f(0.0, 0.0, 0.0);       // black color for drawing
    gluOrtho2D(-320, 320, -240, 240); // set coordinate system from -320 to +320 (x), -240 to +240 (y)
}

// Main Function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle in All Quadrants");
    Init();
    glutDisplayFunc(draw_circles_all_quadrants);
    glutMainLoop();
    return 0;
}
