#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>

using namespace std;

struct Point
{
    float x;
    float y;
};

Point original[100];
Point transformed[100];

int n;
int choice;

float tx, ty;
float sx, sy;
float angle;

void drawPolygon(Point p[])
{
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < n; i++)
    {
        glVertex2f(p[i].x, p[i].y);
    }

    glEnd();
}

void translation()
{
    for (int i = 0; i < n; i++)
    {
        transformed[i].x = original[i].x + tx;
        transformed[i].y = original[i].y + ty;
    }
}

void scaling()
{
    for (int i = 0; i < n; i++)
    {
        transformed[i].x = original[i].x * sx;
        transformed[i].y = original[i].y * sy;
    }
}

void rotation()
{
    float radian = angle * 3.14159265f / 180.0f;

    for (int i = 0; i < n; i++)
    {
        transformed[i].x =
            original[i].x * cos(radian)
            - original[i].y * sin(radian);
        transformed[i].y =
            original[i].x * sin(radian)
            + original[i].y * cos(radian);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Original polygon - White
    glColor3f(1.0f, 1.0f, 1.0f);

    drawPolygon(original);

    // Transformed polygon - Red
    glColor3f(1.0f, 0.0f, 0.0f);

    drawPolygon(transformed);

    glFlush();
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-500, 500, -500, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    cout << "======================================" << endl;
    cout << "       BASIC TRANSFORMATION" << endl;
    cout << "======================================" << endl;

    cout << "1. Translation" << endl;
    cout << "2. Scaling" << endl;
    cout << "3. Rotation" << endl;
    cout << "4. Exit" << endl;

    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 4)
    {
        return 0;
    }

    cout << "\nEnter the no. of edges: ";
    cin >> n;

    cout << "\nEnter the co-ordinates of vertices:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Vertex " << i + 1 << ": ";
        cin >> original[i].x >> original[i].y;
    }

    if (choice == 1)
    {
        cout << "\nEnter the Translation factor for x and y: ";
        cin >> tx >> ty;

        translation();
    }
    else if (choice == 2)
    {
        cout << "\nEnter the Scaling factor for x and y: ";
        cin >> sx >> sy;

        scaling();
    }
    else if (choice == 3)
    {
        cout << "\nEnter the Rotation angle: ";
        cin >> angle;

        rotation();
    }
    else
    {
        cout << "\nInvalid choice!" << endl;
        return 0;
    }

    // Initialize GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 800);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Basic Transformation");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}