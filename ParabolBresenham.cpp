#include <GL/glut.h>
#include <iostream>

int startX = 0, startY = 0;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawParabolic() {
    int a = 1;  // Coefficient of the parabolic equation (y = ax^2)

    int x = 0;
    int y = 0;
    int d = 0;

    while (x <= startY) {
        plot(startX + x, startY - y);
        plot(startX - x, startY - y);
        d += 2 * x + 1;
        if (d >= 0) {
            y++;
            d += 2 - 2 * startY;
        }
        x++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        startX = x;
        startY = glutGet(GLUT_WINDOW_HEIGHT) - y;
        drawParabolic();
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bresenham Parabolic Drawer");

    glClearColor(0.0, 0.0, 0.0, 0.0);  // Màu ðen: R=0, G=0, B=0
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutMainLoop();

    return 0;
}

