#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const float PI = 3.1415926f;

// Animation / position state (stationary car)
float carPosX = 300.0f;
const float carPosY = 180.0f;
const float carSpeed = 0.0f; // stationary

void circle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        float theta = 2.0f * PI * i / 100;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

void drawCar(float x, float y, float r, float g, float b)
{
    // Body
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 180, y);
        glVertex2f(x + 180, y + 40);
        glVertex2f(x, y + 40);
    glEnd();

    // Roof
    glBegin(GL_POLYGON);
        glVertex2f(x + 35, y + 40);
        glVertex2f(x + 60, y + 75);
        glVertex2f(x + 120, y + 75);
        glVertex2f(x + 150, y + 40);
    glEnd();

    // Windows
    glColor3f(0.8f, 0.9f, 1.0f);

    glBegin(GL_QUADS);
        glVertex2f(x + 45, y + 45);
        glVertex2f(x + 80, y + 45);
        glVertex2f(x + 75, y + 68);
        glVertex2f(x + 55, y + 68);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(x + 90, y + 45);
        glVertex2f(x + 135, y + 45);
        glVertex2f(x + 125, y + 68);
        glVertex2f(x + 85, y + 68);
    glEnd();

    // Wheels
    glColor3f(0,0,0);
    circle(x + 45, y - 18, 18);
    circle(x + 140, y - 18, 18);

    // Wheel hubs
    glColor3f(0.7f,0.7f,0.7f);
    circle(x + 45, y - 18, 8);
    circle(x + 140, y - 18, 8);
}

void drawBuilding(float x, float y, float w, float h)
{
    // Building main body
    glColor3f(0.7f, 0.7f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();

    // Roof
    glColor3f(0.6f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 10, y + h);
        glVertex2f(x + w + 10, y + h);
        glVertex2f(x + w / 2, y + h + 40);
    glEnd();

    // Windows grid
    glColor3f(0.95f, 0.97f, 1.0f);
    const int cols = 4;
    const int rows = 5;
    const float winW = 40.0f;
    const float winH = 40.0f;
    float gapX = (w - cols * winW) / (cols + 1);
    float gapY = (h - rows * winH) / (rows + 1);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            float wx = x + gapX + j * (winW + gapX);
            float wy = y + gapY + i * (winH + gapY);
            glBegin(GL_QUADS);
                glVertex2f(wx, wy);
                glVertex2f(wx + winW, wy);
                glVertex2f(wx + winW, wy + winH);
                glVertex2f(wx, wy + winH);
            glEnd();
        }
    }
}

void drawRoad(float y)
{
    // Road base
    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(0, y);
        glVertex2f(800, y);
        glVertex2f(800, y + 120);
        glVertex2f(0, y + 120);
    glEnd();

    // Center continuous line
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(0, y + 60 - 4);
        glVertex2f(800, y + 60 - 4);
        glVertex2f(800, y + 60 + 4);
        glVertex2f(0, y + 60 + 4);
    glEnd();
}

// No update timer: car is stationary

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Building (draw first so car appears in front)
    drawBuilding(150, 100, 400, 400);

    // Road (in front of building)
    drawRoad(60);

    // Single animated car in front of the building
    drawCar(carPosX, carPosY, 1.0f, 0.0f, 0.0f);

    glutSwapBuffers();
}

void init()
{
    glClearColor(1,1,1,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,800,0,600);

    glViewport(0,0,800,600);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Two Overlapping Cars");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}