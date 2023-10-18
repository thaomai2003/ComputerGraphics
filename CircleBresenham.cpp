#include <GL/glut.h>
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
int mouseX = 0;
int mouseY = 0;
int radius = 50;

void drawCircle(int centerX, int centerY, int radius) {
    glBegin(GL_POINTS);
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        glVertex2i(centerX + x, centerY + y);
        glVertex2i(centerX - x, centerY + y);
        glVertex2i(centerX + x, centerY - y);
        glVertex2i(centerX - x, centerY - y);
        glVertex2i(centerX + y, centerY + x);
        glVertex2i(centerX - y, centerY + x);
        glVertex2i(centerX + y, centerY - x);
        glVertex2i(centerX - y, centerY - x);

        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);  // Red color
    drawCircle(mouseX, SCREEN_HEIGHT - mouseY, radius);
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Circle Drawing");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutMainLoop();

    return 0;
}

