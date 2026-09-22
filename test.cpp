#include<windows.h>
 #include <GL/glut.h>
 #define PI 3.1416
 #include<math.h>

// ================= Translation =================

// Rocket
 GLfloat rx = 0.0f;
 GLfloat ry = 0.0f;
 int rocketFlag = 0;

// house
 GLfloat hx = 0.0f;
 GLfloat hy = 0.0f;
 int houseFlag = 0;

// bird
 GLfloat birdx = 0.0f;
 GLfloat birdy = 0.0f;
 int birdFlag = 0;

// Cloud
 GLfloat cx = 0.0f;
 int cloudFlag = 1; //Auto jabe

// ================= Rotation =================

GLfloat angle = 0.0f;
 int rFlag = 0;
 GLfloat speed = 1.0f;

// Turbine
 GLfloat turbineAngle = 0.0f;
 GLfloat turbineSpeed = 2.0f;

// ================= Scaling/Zoom ================

GLfloat scale = 1.0f;
 int scaleFlag = 0;
 GLfloat scaleSpeed = 0.005f;

// Circle Scaling
 GLfloat circleScale = 1.0f;
 int circleScaleFlag = 1;
 GLfloat circleScaleSpeed = 0.005f;

// ================= Speed =================

GLfloat rocketSpeed = 0.005f;
 GLfloat cloudSpeed = 0.005f;
 GLfloat houseSpeed = 0.006f;
 GLfloat birdSpeed = 0.003f;
 GLfloat tarSpeed = 0.005f;

// ================= Mouse Pause / Resume =================

bool paused = false;

int rocketFlagSaved = 0;
 int cloudFlagSaved = 0;
 int houseFlagSaved = 0;

GLfloat rocketSpeedSaved = 0.005f;
 GLfloat cloudSpeedSaved = 0.005f;
 GLfloat houseSpeedSaved = 0.006f;

// ================= Circle Drawing Function =================

void CC(float x, float y, float ra, int r, int g, int b)
 {
 int i;

 GLfloat p1 = x;
 GLfloat q1 = y;
 GLfloat r1 = ra;

 int segments = 40;

 GLfloat fullAngle = 2.0f * PI;

 glBegin(GL_TRIANGLE_FAN);

 glColor3ub(r, g, b);

 glVertex2f(p1, q1);

 for (i = 0; i <= segments; i++)
 {
 glVertex2f(
 p1 + (r1 * cos(i * fullAngle / segments)),
 q1 + (r1 * sin(i * fullAngle / segments))
 );
 }

 glEnd();
 }

// ***** DISPLAY *****
 // ***** DISPLAY *****
 // ***** DISPLAY *****

void display()
 {
 glClearColor(0.529f, 0.808f, 0.900f, 1.0f);

 glClear(GL_COLOR_BUFFER_BIT);

 glLoadIdentity();

 // =====================================================
 // CLOUDS
 // =====================================================

 glPushMatrix();

 glTranslatef(cx, 0.0f, 0.0f);
 glRotatef(angle, 0.0f, 0.0f, 1.0f);

 // ---------------- Cloud 1 ----------------

 CC(-0.4f, 0.5f, 0.13f, 255, 255, 255);

 CC(-0.55f, 0.5f, 0.07f, 255, 255, 255);

 CC(-0.25f, 0.5f, 0.07f, 255, 255, 255);

 // ---------------- Cloud 2 ----------------

 CC(-0.6f, 0.2f, 0.13f, 255, 255, 255);

 CC(-0.75f, 0.2f, 0.07f, 255, 255, 255);

 CC(-0.45f, 0.2f, 0.07f, 255, 255, 255);

 glPopMatrix();

 // =====================================================
 // HOUSE
 // =====================================================

 glPushMatrix();

 glTranslatef(hx, hy, 0.0f);
 glTranslatef(0.65f, 0.15f, 0.0f);
 glRotatef(angle, 0.0f, 0.0f, 1.0f);

 glTranslatef(-0.65f, -0.15f, 0.0f); // Center থেকে আবার original position-এ
 //glScalef(scale, scale, 1.0f); // Scaling apply

 // house Head
 glBegin(GL_QUADS);

 glColor3ub(128, 100, 0);

 glVertex2f(0.5f, 0.0f);
 glVertex2f(0.8f, 0.0f);
 glVertex2f(0.8f, 0.3f);
 glVertex2f(0.5f, 0.3f);

 glEnd();

 // house line
 glBegin(GL_LINES);

 glColor3ub(128, 0, 0);

 glVertex2f(0.5f, 0.1f);
 glVertex2f(0.8f, 0.1f);

 glEnd();

 glPopMatrix();
 // =====================================================
 // ROCKET
 // =====================================================

 glPushMatrix();

 glTranslatef(rx, ry, 0.0f);
 glScalef(scale, scale, 1.0f);

 // Rocket Head
 glBegin(GL_TRIANGLES);

 glColor3ub(255, 0, 0);

 glVertex2f(0.0f, -0.2f);
 glVertex2f(0.0f, 0.0f);
 glVertex2f(-0.2f, 0.0f);

 glEnd();

 // Rocket Body
 glBegin(GL_QUADS);

 glColor3ub(128, 0, 0);

 glVertex2f(0.0f, -0.2f);
 glVertex2f(-0.2f, 0.0f);
 glVertex2f(-0.4f, -0.2f);
 glVertex2f(-0.2f, -0.4f);

 glEnd();

 // Fire 1
 glBegin(GL_TRIANGLES);

 glColor3ub(255, 255, 0);

 glVertex2f(-0.34f, -0.26f);
 glVertex2f(-0.42f, -0.28f);
 glVertex2f(-0.38f, -0.32f);

 glEnd();

 // Fire 2
 glBegin(GL_TRIANGLES);

 glColor3ub(255, 255, 0);

 glVertex2f(-0.26f, -0.34f);
 glVertex2f(-0.34f, -0.36f);
 glVertex2f(-0.3f, -0.42f);

 glEnd();

 glPopMatrix();
 // =====================================================
 // Bird
 // =====================================================

 glPushMatrix();

 glTranslatef(birdx, birdy, 0.0f);

 //glTranslatef(0.65f, 0.15f, 0.0f);
 // glRotatef(angle, 0.0f, 0.0f, 1.0f);
 // glTranslatef(-0.65f, -0.15f, 0.0f);
 //glScalef(scale, scale, 1.0f);

 // line 1
 glBegin(GL_LINES);

 glColor3ub(110, 120, 0);
 glVertex2f(-0.9f, 0.25f);
 glVertex2f(-0.85f, 0.3f);
 glEnd();
 // line 2
 glBegin(GL_LINES);

 glColor3ub(110, 120, 0);
 glVertex2f(-0.8f, 0.25f);
 glVertex2f(-0.85f, 0.3f);
 glEnd();
 // line 3
 glBegin(GL_LINES);

 glColor3ub(110, 120, 0);
 glVertex2f(-0.75f, 0.2f);
 glVertex2f(-0.7f, 0.25f);
 glEnd();
 // line 4
 glBegin(GL_LINES);

 glColor3ub(110, 120, 0);
 glVertex2f(-0.7f, 0.25f);
 glVertex2f(-0.65f, 0.2f);
 glEnd();
 // line 1
 glBegin(GL_LINES);

 glColor3ub(110, 120, 0);
 glVertex2f(-0.6f, 0.25f);
 glVertex2f(-0.55f, 0.3f);
 glEnd();
 // line 2
 glBegin(GL_LINES);

 glColor3ub(110, 120, 0);
 glVertex2f(-0.55f, 0.3f);
 glVertex2f(-0.5f, 0.25f);
 glEnd();

 glPopMatrix();

 // =====================================================
 // tarbine (turbine)
 // =====================================================

 // turbine body
 glBegin(GL_QUADS);

 glColor3ub(128, 100, 0);

 glVertex2f(0.7f, 0.0f);
 glVertex2f(0.8f, 0.0f);
 glVertex2f(0.8f, 0.3f);
 glVertex2f(0.7f, 0.3f);

 glEnd();
 glPushMatrix();

 // Rotation center
 glTranslatef(0.7f, 0.3f, 0.0f);

 // Turbine always rotates
 glRotatef(turbineAngle, 0.0f, 0.0f, 1.0f);

 glTranslatef(-0.7f, -0.3f, 0.0f);

 // Blade 1
 glBegin(GL_LINES);

 glColor3ub(120, 150, 100);

 glVertex2f(0.5f, 0.2f);
 glVertex2f(0.9f, 0.4f);

 glEnd();

 // Blade 2
 glBegin(GL_LINES);

 glColor3ub(120, 150, 100);

 glVertex2f(0.5f, 0.4f);
 glVertex2f(0.9f, 0.2f);

 glEnd();

glPopMatrix();

// =====================================================
 // SMALL CIRCLE scaling
 // =====================================================

glPushMatrix();

 // Circle position
 glTranslatef(0.3f, 0.3f, 0.0f);

 // Small zoom in / zoom out
 glScalef(circleScale, circleScale, 1.0f);

 // Circle
 CC(0.0f, 0.0f, 0.03f, 255, 0, 0);

glPopMatrix();

 glFlush();
 }

// =====================================================
 // KEYBOARD CONTROL
 // =====================================================

void keyboard(unsigned char key, int x, int y)
 {
 switch (key)
 {

 // ---------------- Rocket ----------------

 case 'f':
 // Rocket forward/up
 rocketFlag = 1;
 break;

 case 's':
 // Rocket stop
 rocketFlag = 0;
 break;

 case 'b':
 // Rocket backward/down
 rocketFlag = -1;
 break;

 // ---------------- HOUSE ----------------

 case 'a': // 'a' -> translation(start)
 houseFlag = 1;
 break;
 case 'c': // 'c' -> translation(off)
 houseFlag = 0;
 break;

 // ---------------- bird ----------------

 case 'A': // 'A' -> translation(start)
 birdFlag = 1;
 break;
 case 'B': // 'c' -> translation(off)
 birdFlag = 0;
 break;

// ---------------- rotatioon ----------------

 case 'i': // 'i' -> Rotation শুরু
 rFlag = 1;
 break;
 case 'g': // 'g' -> Rotation বন্ধ
 rFlag = 0;
 break;

 // ================= Scaling =================

 case 'p':
 scaleFlag = 1;
 break;

 case 'o':
 scaleFlag = 0;
 break;

 // ---------------- Cloud ----------------

 /* case 'r':
 // Cloud movement start
 cloudFlag = 1;
 break;

 case 't':
 // Cloud movement stop
 cloudFlag = 0;
 break; */

 // ---------------- Rocket Speed ----------------

 case 'y':
 rocketSpeed = rocketSpeed + 0.001f;
 break;

 case 'u':
 rocketSpeed = rocketSpeed - 0.001f;

 if (rocketSpeed < 0.001f)
 rocketSpeed = 0.001f;

 break;

 // ---------------- Cloud Speed ----------------

 case 'm':
 cloudSpeed = cloudSpeed + 0.001f;
 break;

 case 'n':
 cloudSpeed = cloudSpeed - 0.001f;

 if (cloudSpeed < 0.001f)
 cloudSpeed = 0.001f;

 break;

 // ---------------- HOUSE Speed ----------------

 case 'z':
 houseSpeed = houseSpeed + 0.001f;
 break;

 case 'x':
 houseSpeed = houseSpeed - 0.001f;

 if (houseSpeed < 0.001f)
 houseSpeed = 0.001f;

 break;

 // ---------------- bird Speed ----------------

 case 'C':
 birdSpeed = birdSpeed + 0.001f;
 break;

 case 'D':
 birdSpeed = birdSpeed - 0.001f;

 if (birdSpeed < 0.001f)
 birdSpeed = 0.001f;

 break;

// ---------------- rotation Speed ----------------

 case 'j':
 speed = speed + .5f;
 break;

 case 'k':
 speed = speed - 0.5f;

 if (speed < 0.5f)
 speed = 0.5f;

 break;

// ---------------- scaling Speed ----------------
 case 'w':
 scaleSpeed = scaleSpeed + 0.005f;
 break;
 case 'q':
 scaleSpeed = scaleSpeed - 0.005f;

 if (scaleSpeed < 0.001f)
 scaleSpeed = 0.001f;

 break;

 // ---------------- ESC ----------------

 case 27:
 exit(0);
 break;
 }

 glutPostRedisplay();
 }

// =====================================================
 // MOUSE CONTROL
 // =====================================================

void mouse(int button, int state, int x, int y)
 {

 // ---------------- LEFT CLICK = PAUSE ----------------

 if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
 {

 if (!paused)
 {

 rocketFlagSaved = rocketFlag;

 cloudFlagSaved = cloudFlag;

 rocketSpeedSaved = rocketSpeed;

 cloudSpeedSaved = cloudSpeed;

 // Stop everything

 rocketFlag = 0;

 cloudFlag = 0;

 paused = true;
 }
 }

 // ---------------- RIGHT CLICK = RESUME ----------------

 if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
 {

 if (paused)
 {

 rocketFlag = rocketFlagSaved;

 cloudFlag = cloudFlagSaved;

 rocketSpeed = rocketSpeedSaved;

 cloudSpeed = cloudSpeedSaved;

 paused = false;
 }
 }

 glutPostRedisplay();
 }

// =====================================================
 // UPDATE
 // UPDATE
 // UPDATE
 // UPDATE
 // =====================================================

void update(int value)
 {

 // =================================================
 // ROCKET MOVEMENT
 // =================================================

 if (rocketFlag == 1)
 {

 rx = rx + rocketSpeed;

 ry = ry + rocketSpeed;

 // Rocket screen-এর বাইরে গেলে আবার নিচ থেকে আসবে

 if (rx > 1.3f || ry > 1.3f)
 {

 rx = -0.5f;
 ry = -0.5f;
 }
 }

 // =================================================
 // ROCKET BACKWARD MOVEMENT
 // =================================================

 if (rocketFlag == -1)
 {

 rx = rx - rocketSpeed;

 ry = ry - rocketSpeed;

 // Rocket screen-এর বাইরে গেলে আবার উপরে আসবে

 if (rx < -1.3f || ry < -1.3f)
 {

 rx = 0.5f;
 ry = 0.5f;
 }
 }

 // =================================================
 // House MOVEMENT
 // =================================================

 if (houseFlag == 1)
 {

 hx = hx - houseSpeed;

 if (hx <- 1.5f)
 {

 hx = 0.5f;
 }
 }

 // =================================================
 // Bird MOVEMENT (TARNSLATE)
 // =================================================

 if (birdFlag == 1)
 {

 birdx = birdx + birdSpeed;

 //left --->right
 // house left side-এর বাইরে গেলে <আবার right side থেকে আসবে

 if (birdx > 1.5f)
 {

 birdx = -0.5f;
 }
 }

 // =================================================
 // CLOUD MOVEMENT
 // =================================================

 // if (cloudFlag == 1)
 {

 cx = cx + cloudSpeed;

 // Cloud right side-এর বাইরে গেলে
 // আবার left side থেকে আসবে

 if (cx > 1.5f)
 {

 cx = -0.5f;
 }
 }
 // =================================================
 // Rotation
 // =================================================

 if (rFlag == 1)
 {

 angle = angle + speed;

 if (angle >= 360.0f)
 {
 angle = angle - 360.0f;
 }
 }

 // TURBINE ROTATION

turbineAngle = turbineAngle + turbineSpeed;

if (turbineAngle >= 360.0f)
 {
 turbineAngle = turbineAngle - 360.0f;
 }

// =================================================
 // CIRCLE SCALING
 // =================================================

if (circleScaleFlag == 1)
 {
 circleScale = circleScale + circleScaleSpeed;

 if (circleScale >= 1.15f)
 {
 circleScale = 1.15f;
 circleScaleFlag = -1;
 }
 }

if (circleScaleFlag == -1)
 {
 circleScale = circleScale - circleScaleSpeed;

 if (circleScale <= 0.85f)
 {
 circleScale = 0.85f;
 circleScaleFlag = 1;
 }
 }
 // =================================================
 // SCALING
 // =================================================
 if (scaleFlag == 1)
 {
 scale = scale + scaleSpeed;

 if (scale >= 1.0f)
 {
 scale = 1.0f;
 scaleFlag = -1;
 }
 }

 if (scaleFlag == -1)
 {
 scale = scale - scaleSpeed;

 if (scale <= 0.80f)
 {
 scale = 0.80f;
 scaleFlag = 1;
 }
 }

 glutPostRedisplay();

 glutTimerFunc(16, update, 0);
 }

// =====================================================
 // MAIN
 // =====================================================

int main(int argc, char** argv)
 {

 glutInit(&argc, argv);

 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

 glutInitWindowSize(1000, 600);

 glutCreateWindow("Tarikul Islam Joy");

 // Display
 glutDisplayFunc(display);

 // Keyboard
 glutKeyboardFunc(keyboard);

 // Mouse
 glutMouseFunc(mouse);

 // Timer
 glutTimerFunc(16, update, 0);

 glutMainLoop();

 return 0;
 }