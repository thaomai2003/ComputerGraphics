#include <GL/glut.h>
#include <iostream>

int centerX = 0, centerY = 0;
int a = 1;  // Coefficient of the parabolic equation (y = ax^2)

void plotPoints(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawParabol() {
    int x = 0;
    int y = 0;
    int d = 1 - a;

    plotPoints(x + centerX, y + centerY);
    plotPoints(-x + centerX, y + centerY);

    while (y < 2 * a * x) {
        if (d < 0) {
            d += 2 * a;
        } else {
            d += 2 * a - 2 * (2 * a * x + a) + 4;
            y++;
        }
        x++;
        plotPoints(x + centerX, y + centerY);
        plotPoints(-x + centerX, y + centerY);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    drawParabol();
    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        centerX = x;
        centerY = glutGet(GLUT_WINDOW_HEIGHT) - y;
        a = x / 4;  // Use x coordinate divided by 4 as the coefficient a
        drawParabol();
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Midpoint Parabolic Algorithm");

    glClearColor(0.0, 0.0, 0.0, 0.0);  // Màu n?n ðen

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutMainLoop();

    return 0;
}

