#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <time.h>


const float zNear = 1.0;
const float zFar = 40.0;
const float zoomInit = 1.0;
const int maxObj = 1000;
const int xCamInit = 0;
const int yCamInit = 2;
const int zCamInit = 4;
const int landscapeWidth = 20;
const int viewerRoadWidth = 2;

typedef struct {
  int x;
  int y;
  int z;
  int rotation;
} position;

GLfloat Yx = xCamInit, Yy = yCamInit, Yz = zCamInit, fov = 60;
GLint view_w, view_h;

position viewerPosition;
position worldPosition;
position objVect[maxObj];

float zoom = zoomInit;

void createObjects(int posObjVect)
{
    int randomX;
    int randomY;
    int randomZ;
    int randomRot;

    randomX = rand() % 	(landscapeWidth - viewerRoadWidth);
    randomY = rand() % (int)zFar;
    randomZ = rand() % 2;
    randomRot = rand() % 90;

    if(randomZ == 1)
        objVect[posObjVect].x = -randomX - (viewerRoadWidth + 1);
    else
        objVect[posObjVect].x = randomX + (viewerRoadWidth + 1);

    objVect[posObjVect].y = 0;
    objVect[posObjVect].z = viewerPosition.z - (randomY + zFar);
    objVect[posObjVect].rotation = randomRot;
}

void InitializeObjs()
{
    int i;

    for(i = 0; i < maxObj; i++)
        createObjects(i);
}

void init()
{
    srand(time(NULL));

    viewerPosition.x = 0;
    viewerPosition.y = 0;

    worldPosition.x = 0;
    worldPosition.y = 0;

    InitializeObjs();

    glClearColor(0.000, 0.000, 0.545, 0.0);
    glShadeModel (GL_FLAT);
}


void DrawSnowMen() {

    int i = 0;

    if(objVect[i].z - zFar > viewerPosition.z)
        createObjects(i);

    for (i = 0; i < 15; i++) {
        glColor3f(1.0f, 1.0f, 1.0f);

        glTranslatef(objVect[i].x, objVect[i].y, objVect[i].z);
        glutSolidSphere(0.75f, 20, 20);

        glTranslatef(0.0f, 1.0f, 0.0f);
        glutSolidSphere(0.25f, 20, 20);

        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.05f, 0.10f, 0.18f);
        glutSolidSphere(0.05f, 10, 10);
        glTranslatef(-0.1f, 0.0f, 0.0f);
        glutSolidSphere(0.05f, 10, 10);
        glPopMatrix();

        glColor3f(1.0f, 0.5f, 0.5f);
        glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(0.08f, 0.5f, 10, 2);
    }
}

void DrawnRocks()
{
    int i = 0;

    for(i = 0; i < 15; i++)
    {

        if(objVect[i].z - zFar > viewerPosition.z)
            createObjects(i);

        glColor3f (0.663, 0.663, 0.663);

        glPushMatrix();
            glTranslatef(objVect[i].x, objVect[i].y, objVect[i].z);
            glRotatef(objVect[i].rotation , 0, 1, 0);
            glScalef(.2, .2, .2);
            glutSolidSphere(3, 3, 3);
        glPopMatrix();

        glColor3f (0.663, 0.663, 0.663);
    }
}

void CreateViewerRoad()
{
    glBegin(GL_QUADS);
       glColor3f(0.878, 1.000, 1.000);

       glVertex3i(landscapeWidth, 40, -1*(zFar) + viewerPosition.z);
       glVertex3i(-landscapeWidth, 0, -1*(zFar) + viewerPosition.z);
       glVertex3i(-landscapeWidth, 0, zFar + viewerPosition.z);
       glVertex3i(landscapeWidth, 0, zFar + viewerPosition.z);
    glEnd();
}

void display()
{
    glClear (GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glLoadIdentity();

        gluLookAt (Yx, Yy, Yz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        glTranslatef(worldPosition.x, worldPosition.y, worldPosition.z);

        CreateViewerRoad();
        DrawnRocks();
        DrawSnowMen();
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

void KeyHandle(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            viewerPosition.z -= 1;
            worldPosition.z += 1;
            break;
        case '-':
            if(zoom < zoomInit + 0.5)
                zoom+=0.1;
            break;
        case '+':
            if(zoom > zoomInit - 0.5)
                zoom-=0.1;
            break;

    }

    glutPostRedisplay();
    reshape(view_w, view_h);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (350, 100);
    glutCreateWindow (argv[0]);
    init();
    glutPostRedisplay();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(KeyHandle);
    glutMainLoop();
    return 0;
}