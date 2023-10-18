#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

int center_x, center_y, a, b;

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_ellipse() {
    int x = 0;
    int y = b;
    double d1 = b * b - a * a * b + a * a / 4.0;
    int dx = 2 * b * b * x;
    int dy = 2 * a * a * y;

    while (dx < dy) {
        draw_pixel(x + center_x, y + center_y);
        draw_pixel(-x + center_x, y + center_y);
        draw_pixel(x + center_x, -y + center_y);
        draw_pixel(-x + center_x, -y + center_y);

        x++;

        if (d1 < 0) {
            dx += 2 * b * b;
            d1 += dx + b * b;
        } else {
            y--;
            dx += 2 * b * b;
            dy -= 2 * a * a;
            d1 += dx - dy + b * b;
        }
    }

    double d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;

    while (y >= 0) {
        draw_pixel(x + center_x, y + center_y);
        draw_pixel(-x + center_x, y + center_y);
        draw_pixel(x + center_x, -y + center_y);
        draw_pixel(-x + center_x, -y + center_y);

        y--;

        if (d2 > 0) {
            dx += 2 * b * b;
            dy -= 2 * a * a;
            d2 += a * a - dy;
        } else {
            x++;
            dx += 2 * b * b;
            d2 += 2 * b * b + dx - dy;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // Set color to white
    glPointSize(1.0);  // Set point size

    if (a > 0 && b > 0) {
        draw_ellipse();
    }

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (a <= 0 || b <= 0) {
            center_x = x;
            center_y = glutGet(GLUT_WINDOW_HEIGHT) - y;
            a = 1;
            b = 1;
        } else if (a > 0 && b > 0) {
            a = abs(x - center_x);
            b = abs(glutGet(GLUT_WINDOW_HEIGHT) - y - center_y);
            glutPostRedisplay();
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ellipse Drawing (Midpoint Algorithm)");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

