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

// Draws the Union Jack canton using layered manual polygons.
void drawUnionJack(float x, float y, float width, float height) {
    setColor(1, 33, 105);
    drawRectangle(x, y, width, height);

    setColor(255, 255, 255);
    glLineWidth(36);
    glBegin(GL_LINES);
    glVertex2f(x, y); glVertex2f(x + width, y + height);
    glVertex2f(x + width, y); glVertex2f(x, y + height);
    glEnd();

    setColor(200, 16, 46);
    glLineWidth(18);
    glBegin(GL_LINES);
    glVertex2f(x, y); glVertex2f(x + width, y + height);
    glVertex2f(x + width, y); glVertex2f(x, y + height);
    glEnd();

    setColor(255, 255, 255);
    drawRectangle(x + width / 2.0f - 30, y, 60, height);
    drawRectangle(x, y + height / 2.0f - 30, width, 60);

    setColor(200, 16, 46);
    drawRectangle(x + width / 2.0f - 17, y, 34, height);
    drawRectangle(x, y + height / 2.0f - 17, width, 34);

    glLineWidth(1);
}

// Draws one red Southern Cross star with a white border.
void drawBorderedStar(float centerX, float centerY, float radius) {
    setColor(255, 255, 255);
    drawStar(centerX, centerY, radius, radius * 0.40f);
    setColor(200, 16, 46);
    drawStar(centerX, centerY, radius * 0.68f, radius * 0.27f);
}

// Draws the complete New Zealand flag.
void drawFlag() {
    setColor(1, 33, 105);
    drawRectangle(0, 0, 900, 600);
    drawUnionJack(0, 300, 450, 300);

    drawBorderedStar(655, 455, 35);
    drawBorderedStar(760, 360, 31);
    drawBorderedStar(615, 245, 31);
    drawBorderedStar(805, 185, 27);
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
    glutCreateWindow("Flag of New Zealand");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
