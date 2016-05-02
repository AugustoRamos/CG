#include <iostream>

using namespace std;

//
// Created by augustochaves on 03/04/16.
//

#include <GL/glut.h>
#include <math.h>

#define window_wide 1300
#define window_height 700

using namespace std;

int x1, Y1, x2, y2, dx, dy, iter, radius, xCenter, yCenter;

void setPixel(int x, int y){

    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

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
    setPixel(x,y);

    for (int i = 0; i < xEnd; ++i) {
        x = x+1;

        if(d < 0)
            d = d+const1;
        else{
            y = y+1;
            d = d+const2;
        }
        setPixel(x,y);
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
    setPixel(x,y);

    for (int i = 1; i < iter; ++i) {
        x = x+x_inc;
        y = y+y_inc;
        setPixel(round(x), round(y));
    }

    glEnd();
    glFlush();
}


void setCirclePixel(int xCentro, int yCentro, int x, int y){

    setPixel(xCentro+x, yCentro+y);
    setPixel(xCentro+y, yCentro+x);
    setPixel(xCentro+y, yCentro-x);
    setPixel(xCentro+x, yCentro-y);
    setPixel(xCentro-x, yCentro-y);
    setPixel(xCentro-y, yCentro-x);
    setPixel(xCentro-y, yCentro+x);
    setPixel(xCentro-x, yCentro+y);
}

void bresenhamCircle(void){

    int x = 0, y = radius, d;
    d = 1-radius;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINT);
    setCirclePixel(xCenter, yCenter, x, y);

    while(x < y){
        if(d < 0)
            d = d + 2 * x + 3;
        else{
            d = d + 2 * (x-y) + 5;
            y = y-1;
        }

        x = x+1;
        setCirclePixel(xCenter, yCenter, x, y);
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
    glLoadIdentity();
    gluOrtho2D(0 , 640 , 0 , 480);
}

void configureGL(int argc, char **argv){

    /* Initialise GLUT library */
    glutInit(&argc,argv);
    /* Set the initial display mode */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /* Set the initial window position and size */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(window_wide,window_height);
    /* Create the window with title "Visualização" */
    glutCreateWindow("Visualização");
    /* Initialize drawing colors */
    Init();
}

void getLineCoordinates(){

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
}

void getCircleCoordinates(){

    cout << ("Entre com os pontos da circunferência a ser desenhada\n");
    cout << ("\nX Centro:\n") << endl;
    cin >> xCenter;
    cout << ("\ny Centro:\n") << endl;
    cin >> yCenter;
    cout << ("\nRaio:\n") << endl;
    cin >> radius;
}

int main(int argc, char **argv)
{
    int option;

    cout << ("\n\n--------UNESP Rio Claro---------") << endl;
    cout << ("Ciências da computação") << endl;
    cout << ("Commputação Gráfica - Noturno 2016") << endl;
    cout << ("\nAugusto Chaves Ramos") << endl;
    cout << ("Pedro Hippólito") << endl;

    cout << ("-----------------------------------------------");

    cout << "Opções" << endl;
    cout << "1 - DDA" << endl;
    cout << "2 - Bresenham para linhas" << endl;
    cout << "3 - Bresenham para circuferências" << endl;
    cin >> option;

    switch (option){
        case 1:
            getLineCoordinates();
            configureGL(argc, argv);
            glutDisplayFunc(dda);
            break;
        case 2:
            getLineCoordinates();
            configureGL(argc, argv);
            glutDisplayFunc(bresenhamLine);
            break;
        case 3:
            getCircleCoordinates();
            configureGL(argc, argv);
            glutDisplayFunc(bresenhamCircle);
        default:
            cout << ("Opção inválida");
            break;
    }

    /* Keep displaying untill the program is closed */
    glutMainLoop();


    return 0;
}


