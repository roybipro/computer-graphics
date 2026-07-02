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

// Places all 50 stars in the official staggered 6-5 row arrangement.
void drawCantonStars() {
    setColor(255, 255, 255);
    float startY = 556.0f;
    float rowGap = 40.0f;
    float sixStartX = 34.0f;
    float fiveStartX = 66.0f;
    float columnGap = 64.0f;

    for (int row = 0; row < 9; ++row) {
        int count = (row % 2 == 0) ? 6 : 5;
        float startX = (row % 2 == 0) ? sixStartX : fiveStartX;
        for (int col = 0; col < count; ++col) {
            drawStar(startX + col * columnGap, startY - row * rowGap, 11.5f, 4.6f);
        }
    }
}

// Draws the complete United States flag in a 3:2 display area.
void drawFlag() {
    float stripeHeight = 600.0f / 13.0f;
    for (int i = 0; i < 13; ++i) {
        if (i % 2 == 0) {
            setColor(178, 34, 52);
        } else {
            setColor(255, 255, 255);
        }
        drawRectangle(0, 600 - (i + 1) * stripeHeight, 900, stripeHeight);
    }

    setColor(60, 59, 110);
    drawRectangle(0, 600 - stripeHeight * 7, 378, stripeHeight * 7);
    drawCantonStars();
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
    glutCreateWindow("Flag of the USA");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
