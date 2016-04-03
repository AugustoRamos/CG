#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;


double X1, Y1, X2, Y2;

void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void dda(void){
    int iter;
    double x_inc, y_inc, x, y;

    double dx=(X2-X1);
    double dy=(Y2-Y1);

    if (abs(dx) > abs(dy))
        iter = abs(dx);
    else
        iter = abs(dy);

    x_inc = dx/iter;
    y_inc = dy/iter;
    x = X1;
    y = Y1;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(x,y);

    for (int i = 0; i < iter; ++i) {
        x = x+x_inc;
        y = y+y_inc;
        glVertex2d(round(x), round(y));
    }

    glEnd();

    glFlush();
}

void Init()
{
    /* Set clear color to white */
    glClearColor(1.0,1.0,1.0,0);
    /* Set fill color to black */
    glColor3f(0.0,0.0,0.0);
    /* glViewport(0 , 0 , 640 , 480); */
    /* glMatrixMode(GL_PROJECTION); */
    /* glLoadIdentity(); */
    gluOrtho2D(0 , 640 , 0 , 480);
}

int main(int argc, char **argv)
{
    cout << ("Enter two end points of the line to be drawn:\n");
    cout << ("\n************************************");
    cout << ("\nEnter Point1( X1 , Y1):\n");
    scanf("%lf%lf",&X1,&Y1);
    printf("\n************************************");
    printf("\nEnter Point1( X2 , Y2):\n");
    scanf("%lf%lf",&X2,&Y2);

    /* Initialise GLUT library */
    glutInit(&argc,argv);
    /* Set the initial display mode */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /* Set the initial window position and size */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    /* Create the window with title "DDA_Line" */
    glutCreateWindow("DDA_Line");
    /* Initialize drawing colors */
    Init();
    /* Call the displaying function */
    glutDisplayFunc(dda);
    /* Keep displaying untill the program is closed */
    glutMainLoop();

    return 0;
}


