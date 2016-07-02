#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


const float zNear = 1.0;
const float zFar = 40.0;
const float zoomInicial = 1.0;

const int maxArvores = 1000;
const int xInicialCamera = 0;
const int yInicialCamera = 2;
const int zInicialCamera = 4;
const int larguraLateralMato = 20;
const int larguraLateralPista = 3;

typedef struct {
  int x;
  int y;
  int z;
  int rotacao;
} posicao;

GLfloat Yx = xInicialCamera, Yy = yInicialCamera, Yz = zInicialCamera, fov = 60;
GLint view_w, view_h;

posicao posPersonagem;
posicao posMundo;
posicao vetArvores[maxArvores];

float zoom = zoomInicial;


void CriaArvores(int posVetArvores)
{
    int fatorAleatorioX;
    int fatorAleatorioZ;
    int fatorAleatorioLadoarvore;
    int fatorAleatorioRotacao;

    fatorAleatorioX = rand() % 	(larguraLateralMato - larguraLateralPista);

    fatorAleatorioZ = rand() % (int)zFar;

    fatorAleatorioLadoarvore = rand() % 2;

    fatorAleatorioRotacao = rand() % 90;

    if(fatorAleatorioLadoarvore == 1)
    {
        vetArvores[posVetArvores].x = -fatorAleatorioX - (larguraLateralPista + 1);
    }
    else
    {
        vetArvores[posVetArvores].x = fatorAleatorioX + (larguraLateralPista + 1);
    }


    vetArvores[posVetArvores].y = 0;
    vetArvores[posVetArvores].z = posPersonagem.z - (fatorAleatorioZ + zFar);
    vetArvores[posVetArvores].rotacao = fatorAleatorioRotacao;
    
    //printf("arvores: x %d, y %d, z %d posPersonagem: %d \n", vetArvores[posVetArvores].x, vetArvores[posVetArvores].y, vetArvores[posVetArvores].z, posPersonagem.z );
}

void InicializaArvores()
{
    int contador;
    for(contador = 0; contador < maxArvores; contador++)
    {
        CriaArvores(contador);
    }
}

void init()
{
    srand(time(NULL));

    posPersonagem.x = 0;
    posPersonagem.y = 0;
    posPersonagem.z = 1;

    posMundo.x = 0;
    posMundo.y = 0;
    posMundo.z = 0;

    InicializaArvores();

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void CriaPersonagem()
{
    glColor3f (0.0, 0.5, 1.0);

    glPushMatrix();
        glTranslatef(posPersonagem.x, posPersonagem.y + 0.5, posPersonagem.z);
        glutSolidCube(1);
    glPopMatrix();
}

void DesenhaArvores()
{
    int contador = 0;

    for(contador = 0; contador < maxArvores; contador++)
    {

        if(vetArvores[contador].z - zFar > posPersonagem.z)
        {
            CriaArvores(contador);
        }

        glColor3f (0.5, 0.35, 0.05);

        glPushMatrix();
            glTranslatef(vetArvores[contador].x, vetArvores[contador].y, vetArvores[contador].z);
            glRotatef(vetArvores[contador].rotacao , 0, 1, 0);
            glScalef(0.3, 1, 0.3);
            glutSolidCube(1);
        glPopMatrix();

        glColor3f (0.0, 1.0, 0.0);

        glPushMatrix();
            glTranslatef(vetArvores[contador].x, vetArvores[contador].y + 0.75, vetArvores[contador].z);
            glRotatef(vetArvores[contador].rotacao , 0, 1, 0);
            glutSolidCube(.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(vetArvores[contador].x + 0.5, vetArvores[contador].y + 0.75, vetArvores[contador].z);
            glRotatef(vetArvores[contador].rotacao , 0, 1, 0);
            glutSolidCube(.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(vetArvores[contador].x - 0.5, vetArvores[contador].y + 0.75, vetArvores[contador].z);
            glRotatef(vetArvores[contador].rotacao , 0, 1, 0);
            glutSolidCube(.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(vetArvores[contador].x, vetArvores[contador].y + 0.75, vetArvores[contador].z + 0.5);
            glRotatef(vetArvores[contador].rotacao , 0, 1, 0);
            glutSolidCube(.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(vetArvores[contador].x, vetArvores[contador].y + 0.75, vetArvores[contador].z - 0.5);
            glRotatef(vetArvores[contador].rotacao , 0, 1, 0);
            glutSolidCube(.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(vetArvores[contador].x, vetArvores[contador].y + 1.25, vetArvores[contador].z);
            glRotatef(vetArvores[contador].rotacao , 0, 1, 0);
            glutSolidCube(.5);
        glPopMatrix();
    }
}

void CriaPista()
{
    int a;

    //mato
    glBegin(GL_QUADS);
       glColor3f(0.0f, 1.0f, 0.8f);

       glVertex3i(larguraLateralMato, 0, -1*(zFar) + posPersonagem.z);
       glVertex3i(-larguraLateralMato, 0, -1*(zFar) + posPersonagem.z);
       glVertex3i(-larguraLateralMato, 0, zFar + posPersonagem.z);
       glVertex3i(larguraLateralMato, 0, zFar + posPersonagem.z);
    glEnd();


   //pista
    glBegin(GL_QUADS);
       glColor3f(0.0f, 0.0f, 0.0f);

       glVertex3i(larguraLateralPista, 0, -1*(zFar) + posPersonagem.z);
       glVertex3i(-larguraLateralPista, 0, -1*(zFar) + posPersonagem.z);
       glVertex3i(-larguraLateralPista, 0, zFar + posPersonagem.z);
       glVertex3i(larguraLateralPista, 0, zFar + posPersonagem.z);
    glEnd();


    //Desenha faixas
    glBegin(GL_QUADS);
        glLineWidth(10);
        glColor3f(1.0f, 1.0f, 1.0f);
        for (a = -1*(zFar) + posPersonagem.z; a <= 0; a++)
        {
            if(a % 2 != 0)
            {
                glVertex3f(.1, 0, (a-1));
                glVertex3f(-.1, 0, (a-1));
                glVertex3f(-.1, 0, a);
                glVertex3f(.1, 0, a);
            }
        }
    glEnd();
}

void display()
{
    glClear (GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glLoadIdentity();

        gluLookAt (Yx, Yy, Yz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        glTranslatef(posMundo.x, posMundo.y, posMundo.z);

        CriaPista();

        DesenhaArvores();
        
        CriaPersonagem();
    glPopMatrix();

    glFlush ();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    view_w = w;
    view_h = h;
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(fov * zoom, (GLfloat)view_w / (GLfloat)view_h, zNear, zFar);
    glMatrixMode (GL_MODELVIEW);
}

// Função callback chamada para gerenciar eventos de teclado
void GerenciaTeclado(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 'l':
        case 'L':
        	Yx = sin(90) * 10;
        	Yy = yInicialCamera;
        	Yz = 0;
        	break;
        case 'k':
        case 'K':
        	Yx = sin(180) * 10;
        	Yy = yInicialCamera;
        	Yz = 0;
        	break;
        case 'u':
        case 'U':
        	Yx = 0;
        	Yy = zFar -1;
        	Yz = 0.1;
        	break;        	
        case 'r':
        case 'R':
            Yx = xInicialCamera;
            Yy = yInicialCamera;
            Yz = zInicialCamera;
            zoom = zoomInicial;
            break;
        case '-':
            if(zoom < zoomInicial + 0.5)
            {
                zoom+=0.1;
            }
            break;
        case '+':
            if(zoom > zoomInicial - 0.5)
            {
                zoom-=0.1;
            }
            break;
        case 'w':
        case 'W':
            posPersonagem.z -= 1;
            posMundo.z += 1;
            break;
        case 'a':
        case 'A':
            if(posPersonagem.x > -2)
            {
                posPersonagem.x -= 1;
            }
            break;
        case 'd':
        case 'D':
            if(posPersonagem.x < 2)
            {
                posPersonagem.x += 1;
            }
            break;
    }

    //printf("Camera: x: %f, y: %f, z: %f\n", Yx, Yy, Yz);
    
    glutPostRedisplay();
    reshape(view_w, view_h);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(GerenciaTeclado);
    glutMainLoop();
    return 0;
}
