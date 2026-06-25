// First Basic code for Creating a a dot using standard coding apprroach

/*
#include <GL/glut.h>
void display()
{
    //This is a callback function.// OpenGL automatically calls this function when:

    glClear(GL_COLOR_BUFFER_BIT);   // Clears the screen. Removes old drawings. GL_COLOR_BUFFER_BIT → means clear colour buffer.Think of it like: Erase the board before drawing again.
    glPointSize(100.0f);             // Sets point size to 10 pixels. Default size is very small (1 pixel). So this makes it visible.
    glBegin(GL_POINTS);             // Start drawing a primitive. GL_POINTS means we are drawing points. OpenGL works like: Start → Define → End
    glColor3f(1.0f, 0.0f, 0.0f);// glColor3f() sets RGB colour using 3 float values (0.0–1.0): 1.0 = full intensity, 0.0 = none → (1,0,0)=Red, (0,1,0)=Green, (0,0,1)=Blue
    glVertex2f(125, 200);
    //glColor3f(1.0f, 0.0f, 0.0f);     // glVertex2f() defines a 2D coordinate using 2 float values (x,y); (0,0) is the centre, so it draws the red point at the centre.
    //glVertex2f(1.0f,0.0f);
    glEnd();         // // glEnd() ends the drawing block and must always be used after glBegin().

    glFlush();   // Render now. it means  glEnd() ends the drawing block and must always be used after glBegin().
}

void init()  //This runs once before drawing starts.
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);  .
    glLoadIdentity();
    gluOrtho2D(0, 250, 0, 250);
   // gluOrtho2D(-1, 1, -1, 1);  }

int main(int argc, char** argv)
{
    glutInit(&argc, argv); //Initialises GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,400);
    glutInitWindowPosition(250,150);
    glutCreateWindow("Point testing - OpenGL");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
 return 0;
}

*/


/*
//-------------------------------------------------------------------------------------------------------
// USE of GL_LINES

#include <GL/glut.h>

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(0, 100, 0, 100);
    //gluOrtho2D(-1, 1, -1, 1);  // left, right , bottom , top
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);


        glColor3f(0.0f,0.0f,1.0f);
        glVertex2f(50.0f,50.0f);
        glVertex2f(50,80);

        glVertex2f(50,50);
        glVertex2f(80,50);

        /* // Line 1 (Blue)
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.5f, 0.5f);
        // Line 2 (Red)
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.6f, -0.6f);
         //Line 3 (Green)
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.6f, -0.8f);
        glVertex2f(0.6f, 0.8f);

    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("OpenGL Lines");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

*/
/*
// Rectangle drawing using GL_Quads

#include <GL/glut.h>


void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(-1, 1, -1, 1);

}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw shapes using quads
    glBegin(GL_QUADS);

        // Quad 1 (Red)
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.8f,  0.1f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.2f,  0.1f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.2f,  0.7f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2f(-0.8f,  0.7f);

        // Quad 2 (Green Mixed)
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.7f, -0.6f);
        glVertex2f(-0.1f, -0.6f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2f(-0.1f,  0.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.7f,  0.0f);


    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Quads");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

//---------------------------------------------------------
*/
// traingle
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>


void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(-1, 1, -1, 1);

}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // use of GL_TRIANGLES
    glBegin(GL_TRIANGLES);

        glColor3f(0.0f, 0.0f, 1.0f);   // Blue
        glVertex2f(-0.7f, 0.0f);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(-0.4f, 0.3f);

        //Triangle (Mixed Colors)
        glColor3f(1.0f, 0.0f, 0.0f);   // Red
        glVertex2f(0.3f, -0.4f);

        glColor3f(0.0f, 1.0f, 0.0f);   // Green
        glVertex2f(0.9f, -0.4f);

        glColor3f(0.0f, 0.0f, 1.0f);   // Blue
        glVertex2f(0.6f, -0.9f);

    glEnd();
    // Use Of GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);

        glColor3f(0.0f, 0.0f, 1.0f);

        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.5f, 0.25f);


    glEnd();


    // Use of polygons
    glBegin(GL_POLYGON);

        glVertex2f(-0.2f, 0.0f);
        glVertex2f( -0.1f, 0.2f);
        glVertex2f( .3f,  0.6f);
        glVertex2f(0.5f,  0.5f);
        glVertex2f(0.7f,  0.5f);

    glEnd();



    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("OpenGL Triangles");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


//------------------------------------


/*
//  -----------------------------------------------------------------------------------------------------
//   With DDA algorithm
#include <GL/glut.h>
#include <cmath>
void drawLineDDA_mLess1(float x1, float y1, float x2, float y2)
{

    float dx = x2 - x1;
    float dy = y2 - y1;
    float m = dy / dx;
    float x = x1;
    float y = y1;
    glBegin(GL_POINTS);

        for (int i = 0; i <= (int)dx; i++)
        {
            glVertex2f(x, y);
            x = x + 1;
            y = y + m; //make it round according to the rule // for m is less than 1
        }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);
    glColor3f(1.0f, 0.0f, 0.0f);   // Red
    // Example points (pixel coordinates)
    drawLineDDA_mLess1(250,250 ,400, 400);
    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    // IMPORTANT: Use pixel coordinate system so x+1 means "one pixel step"
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA (|m|<=1) using GL_POINTS");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

// -----------------------------------------------------------------------------------------------------//
*/
