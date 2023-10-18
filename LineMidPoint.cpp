#include <GL/glut.h>
#include <cstdlib>
#include <iostream>

int x1, y1, x2, y2;

void drawLineMidpoint(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int dx2 = dx * 2;
    int dy2 = dy * 2;
    
    int ix = (x1 < x2) ? 1 : -1;
    int iy = (y1 < y2) ? 1 : -1;
    
    int x = x1;
    int y = y1;

    if (dx > dy) {
        int err = dy2 - dx;
        while (x != x2) {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            
            if (err >= 0) {
                if (err || (ix > 0)) {
                    y += iy;
                    err -= dx2;
                }
            }
            x += ix;
            err += dy2;
        }
    } else {
        int err = dx2 - dy;
        while (y != y2) {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            
            if (err >= 0) {
                if (err || (iy > 0)) {
                    x += ix;
                    err -= dy2;
                }
            }
            y += iy;
            err += dx2;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    drawLineMidpoint(x1, y1, x2, y2);
    glFlush();
}

void mouse(int button, int state, int mouseX, int mouseY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x1 = mouseX;
        y1 = glutGet(GLUT_WINDOW_HEIGHT) - mouseY;
        std::cout << "Click the starting point of the line: (" << x1 << ", " << y1 << ")\n";
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        x2 = mouseX;
        y2 = glutGet(GLUT_WINDOW_HEIGHT) - mouseY;
        std::cout << "Click the ending point of the line: (" << x2 << ", " << y2 << ")\n";

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Midpoint Line Drawing");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}

