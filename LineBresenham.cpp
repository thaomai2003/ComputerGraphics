#include <GL/glut.h>
#include <cstdlib>
#include <iostream>

int startX, startY, endX, endY;

void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (x1 != x2 || y1 != y2) {
        glBegin(GL_POINTS);
        glVertex2i(x1, y1);
        glEnd();
        
        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white

    // Draw lines with different slopes using Bresenham's algorithm
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    drawLineBresenham(startX, startY, endX, endY);

    glFlush();
}

void handleMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Save the starting point of the line
        startX = x;
        startY = glutGet(GLUT_WINDOW_HEIGHT) - y;
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // Save the ending point of the line
        endX = x;
        endY = glutGet(GLUT_WINDOW_HEIGHT) - y;

        // Redraw the scene
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bresenham Line Drawing");
    init();

    // Register the display callback function
    glutDisplayFunc(display);
    glutMouseFunc(handleMouseClick);

    glutMainLoop();
    return 0;
}

