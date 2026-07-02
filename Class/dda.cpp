

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cmath>

void drawLineDDA(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);

    // Vertical line
    if (dx == 0)
    {
        int step = (dy > 0) ? 1 : -1;

        while ((step > 0 && y <= y2) || (step < 0 && y >= y2))
        {
            glVertex2f(round(x), round(y));
            y += step;
        }
    }
    else
    {
        float m = dy / dx;

        // |m| <= 1
        if (fabs(m) <= 1)
        {
            int step = (dx > 0) ? 1 : -1;

            while ((step > 0 && x <= x2) || (step < 0 && x >= x2))
            {
                glVertex2f(round(x), round(y));
                x += step;
                y += m * step;
            }
        }
        // |m| > 1
        else
        {
            int step = (dy > 0) ? 1 : -1;

            while ((step > 0 && y <= y2) || (step < 0 && y >= y2))
            {
                glVertex2f(round(x), round(y));
                x += (1.0f / m) * step;
                y += step;
            }
        }
    }

    glEnd();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 500, 0, 500);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(4);
    glColor3f(1.0f, 0.0f, 0.0f);

    // Triangle vertices
    drawLineDDA(100,100,400,100);
    drawLineDDA(400,100,250,400);
    drawLineDDA(250,400,100,100);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);

    glutCreateWindow("Triangle using DDA");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}