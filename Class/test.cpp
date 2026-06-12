#include <OpenGL/gl.h>
    #include <GLUT/glut.h>
    #include <OpenGL/glu.h>
    #include <OpenGL/glext.h>

float angle = 0.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);

    // Sphere
    glPushMatrix();
    glTranslatef(-2.5f, 1.5f, -8.0f);
    glRotatef(angle, 1, 1, 0);
    glutWireSphere(0.8, 20, 20);
    glPopMatrix();

    // Cone
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, -8.0f);
    glRotatef(angle, 1, 1, 0);
    glutWireCone(0.8, 1.5, 20, 20);
    glPopMatrix();

    // Torus
    glPushMatrix();
    glTranslatef(2.5f, 1.5f, -8.0f);
    glRotatef(angle, 1, 1, 0);
    glutWireTorus(0.2, 0.8, 20, 20);
    glPopMatrix();

    // Cube
    glPushMatrix();
    glTranslatef(-2.5f, -1.5f, -8.0f);
    glRotatef(angle, 1, 1, 0);
    glutSolidCube(1.2);
    glPopMatrix();

    // Teapot
    glPushMatrix();
    glTranslatef(0.0f, -1.5f, -8.0f);
    glRotatef(angle, 1, 1, 0);
    glutSolidTeapot(0.7);
    glPopMatrix();

    // Sphere Solid
    glPushMatrix();
    glTranslatef(2.5f, -1.5f, -8.0f);
    glRotatef(angle, 1, 1, 0);
    glutSolidSphere(0.8, 20, 20);
    glPopMatrix();

    glutSwapBuffers();
}

void idle()
{
    angle += 0.3f;
    if(angle > 360.0f)
        angle -= 360.0f;

    glutPostRedisplay();
}

void init()
{
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0/600.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("GLUT Shapes Demo - Nigel Stewart Style");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}