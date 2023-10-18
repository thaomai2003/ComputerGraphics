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
    int a_sqr = a * a;
    int b_sqr = b * b;
    int two_a_sqr = 2 * a_sqr;
    int two_b_sqr = 2 * b_sqr;
    int four_a_sqr = 4 * a_sqr;
    int four_b_sqr = 4 * b_sqr;
    float region1 = b_sqr - a_sqr * b + 0.25 * a_sqr;
    int dx = two_b_sqr * x;
    int dy = two_a_sqr * y;

    while (dx < dy) {
        draw_pixel(x + center_x, y + center_y);
        draw_pixel(-x + center_x, y + center_y);
        draw_pixel(x + center_x, -y + center_y);
        draw_pixel(-x + center_x, -y + center_y);

        x += 1;
        dx += four_b_sqr;

        if (region1 < 0) {
            region1 += dx + b_sqr;
        } else {
            y -= 1;
            dy -= four_a_sqr;
            region1 += dx - dy + b_sqr;
        }
    }

    float region2 = b_sqr * (x + 0.5) * (x + 0.5) + a_sqr * (y - 1) * (y - 1) - a_sqr * b_sqr;

    while (y >= 0) {
        draw_pixel(x + center_x, y + center_y);
        draw_pixel(-x + center_x, y + center_y);
        draw_pixel(x + center_x, -y + center_y);
        draw_pixel(-x + center_x, -y + center_y);

        y -= 1;
        dy -= four_a_sqr;

        if (region2 > 0) {
            region2 += a_sqr - dy;
        } else {
            x += 1;
            dx += four_b_sqr;
            region2 += a_sqr + dx;
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
    glutCreateWindow("Ellipse Drawing");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

