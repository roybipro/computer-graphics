#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(100.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();
    glFlush();
}

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 400);
    glutInitWindowPosition(250, 150);
    glutCreateWindow("OpenGL Point Testing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;

}