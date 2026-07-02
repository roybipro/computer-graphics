#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;

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

// Draws a four-point polygon used for the Y-shaped bands.
void drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

// Draws the complete South African flag with layered bands.
void drawFlag() {
    setColor(222, 56, 49);
    drawRectangle(0, 300, 900, 300);
    setColor(0, 35, 149);
    drawRectangle(0, 0, 900, 300);

    setColor(255, 255, 255);
    drawQuad(0, 600, 0, 485, 330, 300, 900, 300);
    drawQuad(0, 0, 0, 115, 330, 300, 900, 300);

    setColor(0, 122, 77);
    drawQuad(0, 600, 0, 515, 300, 345, 900, 345);
    drawQuad(0, 0, 0, 85, 300, 255, 900, 255);
    drawRectangle(300, 255, 600, 90);

    setColor(255, 182, 18);
    drawTriangle(0, 0, 0, 600, 285, 300);

    setColor(0, 0, 0);
    drawTriangle(0, 70, 0, 530, 230, 300);

    setColor(0, 122, 77);
    drawQuad(0, 515, 0, 475, 315, 300, 900, 300);
    drawQuad(0, 85, 0, 125, 315, 300, 900, 300);
    drawRectangle(315, 255, 585, 90);
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
    glutCreateWindow("Flag of South Africa");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
