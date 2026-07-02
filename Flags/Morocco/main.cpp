#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;
const float PI = 3.1415926535f;

// Sets a drawing color using 0-255 RGB values.
void setColor(float r, float g, float b) {
    glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
}

// Draws a filled rectangle from its bottom-left corner.
void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Draws Morocco's interlaced green pentagram as line segments.
void drawPentagram(float centerX, float centerY, float radius) {
    float x[5], y[5];
    for (int i = 0; i < 5; ++i) {
        float angle = PI / 2.0f + i * 2.0f * PI / 5.0f;
        x[i] = centerX + std::cos(angle) * radius;
        y[i] = centerY + std::sin(angle) * radius;
    }

    int order[] = {0, 2, 4, 1, 3, 0};
    setColor(0, 98, 51);
    glLineWidth(12);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 5; ++i) {
        glVertex2f(x[order[i]], y[order[i]]);
    }
    glEnd();
    glLineWidth(1);
}

// Draws the complete Moroccan flag.
void drawFlag() {
    setColor(193, 39, 45);
    drawRectangle(0, 0, 900, 600);
    drawPentagram(450, 300, 135);
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawFlag();
    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Flag of Morocco");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
