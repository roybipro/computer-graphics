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

// Draws a mathematically generated five-point star.
void drawStar(float centerX, float centerY, float outerRadius, float innerRadius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (int i = 0; i <= 10; ++i) {
        float angle = PI / 2.0f + i * PI / 5.0f;
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        glVertex2f(centerX + std::cos(angle) * radius, centerY + std::sin(angle) * radius);
    }
    glEnd();
}

// Draws the complete Ghanaian flag.
void drawFlag() {
    setColor(206, 17, 38);
    drawRectangle(0, 400, 900, 200);
    setColor(252, 209, 22);
    drawRectangle(0, 200, 900, 200);
    setColor(0, 107, 63);
    drawRectangle(0, 0, 900, 200);

    setColor(0, 0, 0);
    drawStar(450, 300, 92, 37);
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
    glutCreateWindow("Flag of Ghana");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
