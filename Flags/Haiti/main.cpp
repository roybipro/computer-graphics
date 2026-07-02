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

// Draws a filled triangle.
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

// Draws a filled polygon circle approximation.
void drawCircle(float centerX, float centerY, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * 2.0f * PI / segments;
        glVertex2f(centerX + std::cos(angle) * radius, centerY + std::sin(angle) * radius);
    }
    glEnd();
}

// Draws a small cannon using primitive shapes.
void drawCannon(float x, float y, bool flip) {
    float direction = flip ? -1.0f : 1.0f;
    setColor(120, 80, 35);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + direction * 72, y + 18);
    glVertex2f(x + direction * 68, y + 32);
    glVertex2f(x - direction * 4, y + 14);
    glEnd();

    setColor(40, 40, 40);
    drawCircle(x + direction * 18, y - 2, 10, 24);
    drawCircle(x + direction * 50, y + 6, 10, 24);
}

// Draws Haiti's simplified coat of arms manually.
void drawCoatOfArms(float centerX, float centerY) {
    setColor(255, 255, 255);
    drawRectangle(centerX - 145, centerY - 95, 290, 190);

    setColor(0, 120, 70);
    drawTriangle(centerX - 45, centerY - 30, centerX + 45, centerY - 30, centerX, centerY + 50);
    setColor(20, 120, 55);
    drawRectangle(centerX - 8, centerY - 30, 16, 92);

    setColor(70, 50, 30);
    drawRectangle(centerX - 70, centerY - 62, 140, 20);
    drawRectangle(centerX - 55, centerY - 82, 110, 20);
    setColor(170, 120, 45);
    drawCannon(centerX - 75, centerY - 62, false);
    drawCannon(centerX + 75, centerY - 62, true);

    setColor(210, 170, 35);
    drawRectangle(centerX - 5, centerY - 50, 10, 112);
    setColor(20, 40, 170);
    drawRectangle(centerX + 5, centerY + 25, 45, 26);
    setColor(210, 40, 40);
    drawRectangle(centerX + 5, centerY + 51, 45, 26);

    setColor(70, 110, 50);
    glLineWidth(3);
    glBegin(GL_LINES);
    for (int i = -3; i <= 3; ++i) {
        glVertex2f(centerX, centerY - 5);
        glVertex2f(centerX + i * 22, centerY + 48 - std::abs(i) * 7);
    }
    glEnd();
    glLineWidth(1);

    setColor(245, 210, 65);
    drawRectangle(centerX - 85, centerY - 95, 170, 18);
}

// Draws the complete Haitian flag.
void drawFlag() {
    setColor(0, 32, 159);
    drawRectangle(0, 300, 900, 300);
    setColor(210, 16, 52);
    drawRectangle(0, 0, 900, 300);
    drawCoatOfArms(450, 300);
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
    glutCreateWindow("Flag of Haiti");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
