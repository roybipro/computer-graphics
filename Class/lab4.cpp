#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

void putPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void midpointLine(int x1, int y1, int x2, int y2)
{
    int dx, dy, d, incrE, incrNE;

    dx = x2 - x1;
    dy = y2 - y1;

    d = 2 * dy - dx;
    incrE = 2 * dy;
    incrNE = 2 * (dy - dx);

    while (x1 <= x2)
    {
        putPixel(x1, y1);

        if (d <= 0)
        {
            d += incrE;
        }
        else
        {
            d += incrNE;
            y1++;
        }

        x1++;
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 500, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0);

    midpointLine(100, 100, 200, 250);
    midpointLine(100, 100, 300, 100);
    midpointLine(150, 100, 300, 200);
    midpointLine(150, 100, 400, 250);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Midpoint Line Algorithm");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}