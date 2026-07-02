#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

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

// Draws the Canadian maple leaf from manually plotted normalized points.
void drawMapleLeaf(float centerX, float centerY, float scale) {
    const float points[][2] = {
        {0.00f, 1.55f}, {-0.13f, 1.03f}, {-0.42f, 1.18f}, {-0.30f, 0.72f},
        {-0.78f, 0.92f}, {-0.58f, 0.46f}, {-1.05f, 0.44f}, {-0.66f, 0.10f},
        {-0.90f, -0.20f}, {-0.38f, -0.17f}, {-0.42f, -0.62f}, {-0.12f, -0.35f},
        {-0.06f, -1.18f}, {0.06f, -1.18f}, {0.12f, -0.35f}, {0.42f, -0.62f},
        {0.38f, -0.17f}, {0.90f, -0.20f}, {0.66f, 0.10f}, {1.05f, 0.44f},
        {0.58f, 0.46f}, {0.78f, 0.92f}, {0.30f, 0.72f}, {0.42f, 1.18f},
        {0.13f, 1.03f}
    };

    setColor(255, 0, 0);
    glBegin(GL_POLYGON);
    for (const auto &point : points) {
        glVertex2f(centerX + point[0] * scale, centerY + point[1] * scale);
    }
    glEnd();
}

// Draws the complete Canadian flag in a 2:1 ratio.
void drawFlag() {
    setColor(255, 255, 255);
    drawRectangle(0, 0, 900, 600);

    setColor(255, 0, 0);
    drawRectangle(0, 0, 225, 600);
    drawRectangle(675, 0, 225, 600);

    drawMapleLeaf(450, 315, 125);
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
    glutCreateWindow("Flag of Canada");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
