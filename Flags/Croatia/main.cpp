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

// Draws the lower shield outline.
void drawShieldBase(float x, float y, float width, float height) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y + height * 0.18f);
    glVertex2f(x + width * 0.50f, y);
    glVertex2f(x, y + height * 0.18f);
    glEnd();
}

// Draws a four-point checker cell.
void drawCell(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Draws a manually clipped polygon cell near the pointed bottom of the shield.
void drawClippedCell(const float points[][2], int count) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < count; ++i) {
        glVertex2f(points[i][0], points[i][1]);
    }
    glEnd();
}

// Draws the red and white checkerboard shield.
void drawCheckerShield(float x, float y, float width, float height) {
    setColor(245, 245, 245);
    drawShieldBase(x, y, width, height);

    float cellW = width / 5.0f;
    float cellH = height / 5.0f;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            if ((row + col) % 2 == 0) {
                setColor(255, 0, 0);
            } else {
                setColor(255, 255, 255);
            }
            drawCell(x + col * cellW, y + height - (row + 1) * cellH,
                     x + (col + 1) * cellW, y + height - row * cellH);
        }
    }

    setColor(255, 0, 0);
    float bottomTop = y + cellH;
    float sideJoinY = y + height * 0.18f;
    float centerX = x + width * 0.50f;
    float p0[][2] = {{x, sideJoinY}, {x, bottomTop}, {x + cellW, bottomTop}, {x + cellW, y + 24.8f}};
    float p2[][2] = {{x + 2 * cellW, bottomTop}, {x + 3 * cellW, bottomTop},
                     {x + 3 * cellW, y + 8.3f}, {centerX, y}, {x + 2 * cellW, y + 8.3f}};
    float p4[][2] = {{x + 4 * cellW, bottomTop}, {x + 5 * cellW, bottomTop},
                     {x + 5 * cellW, sideJoinY}, {x + 4 * cellW, y + 24.8f}};
    drawClippedCell(p0, 4);
    drawClippedCell(p2, 5);
    drawClippedCell(p4, 4);

    setColor(220, 220, 220);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y + height * 0.18f);
    glVertex2f(x + width * 0.50f, y);
    glVertex2f(x, y + height * 0.18f);
    glEnd();
    glLineWidth(1);
}

// Draws five simplified crown shields above the main shield.
void drawCrown(float centerX, float baseY) {
    float shieldW = 42;
    for (int i = 0; i < 5; ++i) {
        float x = centerX - 110 + i * 55;
        if (i == 0 || i == 4) setColor(0, 87, 183);
        if (i == 1 || i == 3) setColor(255, 255, 255);
        if (i == 2) setColor(0, 87, 183);
        glBegin(GL_POLYGON);
        glVertex2f(x, baseY + 55);
        glVertex2f(x + shieldW, baseY + 55);
        glVertex2f(x + shieldW, baseY + 12);
        glVertex2f(x + shieldW / 2, baseY);
        glVertex2f(x, baseY + 12);
        glEnd();

        setColor(255, 0, 0);
        if (i == 1) drawRectangle(x + 16, baseY + 8, 10, 38);
        if (i == 3) drawRectangle(x + 7, baseY + 27, 28, 8);
        if (i == 4) drawCircle(x + 21, baseY + 30, 13, 24);
    }
}

// Draws the complete Croatian flag.
void drawFlag() {
    setColor(255, 0, 0);
    drawRectangle(0, 400, 900, 200);
    setColor(255, 255, 255);
    drawRectangle(0, 200, 900, 200);
    setColor(23, 23, 150);
    drawRectangle(0, 0, 900, 200);

    drawCrown(450, 355);
    drawCheckerShield(355, 185, 190, 230);
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
    glutCreateWindow("Flag of Croatia");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
