#include <iostream>

using namespace std;

//
// Created by augustochaves on 03/04/16.
//

#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int x1, Y1, x2, y2, dx, dy, iter;


void bresenhamLine(void){
    double dx = abs(x2-x1);
    double dy = abs(y2-Y1);
    double d = 2*dy-dx;
    int const1 = 2*dy;
    int const2 = 2 * (dy-dx);
    int xEnd = 0, y =0, x=0;


    if(x1 > x2){
        x = x2;
        y = y2;
        xEnd = x1;
    }
    else{
        x = x1;
        y = Y1;
        xEnd = x2;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(x,y);

    for (int i = 0; i < xEnd; ++i) {
        x = x+1;

        if(d < 0)
            d = d+const1;
        else{
            y = y+1;
            d = d+const2;
        }
        glVertex2d(x,y);
    }

    glEnd();

    glFlush();
}
void dda(void){

    double x_inc, y_inc, x, y;

    dx=(x2-x1);
    dy = y2 - Y1;

    if (abs(dx) > abs(dy))
        iter = abs(dx);
    else
        iter = abs(dy);

    x_inc = dx/iter;
    y_inc = dy/iter;
    x = x1;
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
    glViewport(0 , 0 , 640 , 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0 , 640 , 0 , 480);
}

int main(int argc, char **argv)
{
    int option;

    cout << ("Augusto Chaves Ramos e Pedro Hippolito") << endl;
    cout << ("-----------------------------------------------");
    cout << ("Entre com os pontos da linha a ser desenhada\n");

    cout << ("\nX1:\n") << endl;
    cin >> x1;
    cout << ("\ny1:\n") << endl;
    cin >> Y1;
    cout << "\n-----------------------------------------------";
    cout << ("\nX2:\n") << endl;
    cin >> x2;
    cout << ("\ny2:\n") << endl;
    cin >> y2;

    cout << "Opções" << endl;
    cout << "1 - DDA" << endl;
    cout << "2 - Bresenham para linhas" << endl;
    cout << "3 - Bresenham para circuferências" << endl;
    cin >> option;

    /* Initialise GLUT library */
    glutInit(&argc,argv);
    /* Set the initial display mode */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /* Set the initial window position and size */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    /* Create the window with title "Visualização" */
    glutCreateWindow("Visualização");
    /* Initialize drawing colors */
    Init();

    switch (option){
        case 1:
            glutDisplayFunc(dda);
            break;
        case 2:
            glutDisplayFunc(bresenhamLine);
            break;
        default:
            cout << ("Opção inválida");
            break;
    }

    /* Keep displaying untill the program is closed */
    glutMainLoop();

    return 0;
}


