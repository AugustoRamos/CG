//
// Created by augustochaves on 01/05/16.
//

#include <unistd.h>
#include <graphics.h>
#include <X11/Xlib.h>

#define M_PI 3.14159265358979323846

float originalMatrix[10][2];
int edges;

void switchShow(float mat2[10][2]);
void scale(float matrix[10][2]);
void translation(float matrix[10][2]);
void rotation(float matrix[10][2]);
void mirroring(float matrix[10][2]);
void shear(float matrix[10][2]);

void show(float mat2[10][2]){
    XInitThreads();
    int gd=DETECT,gm, i;

    initgraph(&gd,&gm,NULL);
    setcolor(BLUE);

    for(i=0;i<edges;i++)
    {
        line(originalMatrix[i][0],originalMatrix[i][1],originalMatrix[i+1][0],originalMatrix[i+1][1]);
        sleep(500);
    }

    setcolor(RED);
    for(i=0;i<edges;i++)
    {
        line(mat2[i][0],mat2[i][1],mat2[i+1][0],mat2[i+1][1]);
        sleep(500);
    }
    getch();
    closegraph();
}

void switchShow(float mat2[10][2]){
    int i;

    mat2[edges][0]=mat2[0][0]; // Xaresta = X1
    mat2[edges][1]=mat2[0][1]; // Yaresta = X1

    printf("\nSelecione uma opção: \n\n0- EXIBIR\n\n1- Translacao\n2- Escala\n3- Rotacao\n4- Espelhamento\n5- Cisalhamento\n\n6- VOLTAR\n\n");
    scanf("%d",&i);

    switch (i){
        case 1:
            translation(mat2);
            break;
        case 2:
            scale(mat2);
            break;
        case 3:
            rotation(mat2);
            break;
        case 4:
            mirroring(mat2);
            break;
        case 5:
            shear(mat2);
            break;
        case 0:
            show(mat2);
            break;
    }
}

void translation(float matrix[10][2]){
    float transformationMatrix[10][2],x,y;
    int i;

    printf("\nPonto X,Y para o vetor de translation a partir da origem:\nX:");
    scanf("%f",&x);
    printf("Y:");
    scanf("%f",&y);

    for (i=0;i<edges;i++){
        transformationMatrix[i][0] = matrix[i][0] + x;
        transformationMatrix[i][1] = matrix[i][1] + y;
    }

    transformationMatrix[edges][0]=transformationMatrix[0][0]; // Xaresta = X1
    transformationMatrix[edges][1]=transformationMatrix[0][1]; // Yaresta = X1

    switchShow(transformationMatrix);
}

void scale(float matrix[10][2]){
    float transformationMatrix[10][2],x,y;
    int i;

    printf("\nFator de scale para o eixo X:");
    scanf("%f",&x);
    printf("\nFator de scale para o eixo Y:");
    scanf("%f",&y);

    float x_origem = matrix[0][0];
    float y_origem = matrix[0][1];

    transformationMatrix[0][0] = x_origem;
    transformationMatrix[0][1] = y_origem;

    for (i=1;i<edges;i++){
        transformationMatrix[i][0] = (matrix[i][0] - x_origem) * x + x_origem;
        transformationMatrix[i][1] = (matrix[i][1] - y_origem) * y + y_origem;
    }

    transformationMatrix[edges][0]=transformationMatrix[0][0]; // Xaresta = X1
    transformationMatrix[edges][1]=transformationMatrix[0][1]; // Yaresta = X1

    switchShow(transformationMatrix);
}

void rotation(float matrix[10][2]){
    float a,transformationMatrix[10][2];
    int i;

    printf("\nAngulo de rotation(graus): ");
    scanf("%f",&a);

    a = a*(M_PI/180);
    float sine = sin(a);
    float cosine = cos(a);

    float xOrigin = matrix[0][0];
    float yOrigin = matrix[0][1];

    transformationMatrix[0][0] = xOrigin;
    transformationMatrix[0][1] = yOrigin;

    for (i=1;i<edges;i++){
        transformationMatrix[i][0] = xOrigin + (matrix[i][0]-xOrigin) * cosine - (matrix[i][1]-yOrigin) * sine;
        transformationMatrix[i][1] = yOrigin + (matrix[i][1]-yOrigin) * cosine + (matrix[i][0]-xOrigin) * sine;
    }

    transformationMatrix[edges][0]=transformationMatrix[0][0]; // Xaresta = X1
    transformationMatrix[edges][1]=transformationMatrix[0][1]; // Yaresta = X1

    switchShow(transformationMatrix);
}

void mirroring(float matrix[10][2]){
    float transformationMatrix[10][2];
    float x = 1;
    float y = 1;
    int i;

    printf("\nEspelhar em qual eixo?\n1 - X\n2 - Y\n:");
    scanf("%d",&i);
    if (i == 1) y = -1; else x = -1;

    float xOrigin = matrix[0][0];
    float yOrigin = matrix[0][1];

    transformationMatrix[0][0] = xOrigin;
    transformationMatrix[0][1] = yOrigin;

    for (i=1;i<edges;i++){
        transformationMatrix[i][0] = (matrix[i][0] - xOrigin) * x + xOrigin;
        transformationMatrix[i][1] = (matrix[i][1] - yOrigin) * y + yOrigin;
    }

    transformationMatrix[edges][0]=transformationMatrix[0][0];
    transformationMatrix[edges][1]=transformationMatrix[0][1];

    switchShow(transformationMatrix);
}

void shear(float matrix[10][2]){
    float transformationMatrix[10][2];
    int i;
    float k;

    float xOrigin = matrix[0][0];
    float yOrigin = matrix[0][1];
    transformationMatrix[0][0] = xOrigin;
    transformationMatrix[0][1] = yOrigin;

    printf("\nCisalhamento\nDeseja distorcer com relacao a qual eixo?\n1- X\n2- Y\n");
    scanf("%d",&i);
    printf("\nEscala para distorcer:\n");
    scanf("%f",&k);

    if (i == 1){
        for (i=1;i<edges;i++){
            transformationMatrix[i][0] = matrix[i][0] + k * abs(matrix[i][1] - yOrigin);
            transformationMatrix[i][1] = matrix[i][1];
        }
    }else{
        for (i=0;i<edges;i++){
            transformationMatrix[i][0] = matrix[i][0];
            transformationMatrix[i][1] = matrix[i][1] + k * abs(matrix[i][0] - xOrigin);
        }
    }

    transformationMatrix[edges][0]=transformationMatrix[0][0]; // Xaresta = X1
    transformationMatrix[edges][1]=transformationMatrix[0][1]; // Yaresta = X1

    switchShow(transformationMatrix);
}
int main( )
{
    int reset;
    int i,option;
    int custom = 0;

    printf("\n\nUNESP - RIO CLARO - 05/2016\n\n"
                   "Parte 3 do trabalho 1 de Computacao Grafica - Noturno\n"
                   "Augusto Chaves Ramos\n"
                   "Pedro Hippólito\n"
                   "\nHá um pentágono padrão para a execução do programa, caso queira outro polígono, utilize a opção: '9- MATRIZ PERSONALIZADA' \n");
    do{
        reset = 0;

        // Leitura de dados (x,y) para construção do poligno
        if (custom == 1){
            do{
                printf("Digite o numero de pontos no plano(minimo: 2 maximo 9):\n");
                scanf("%d",&edges);
            } while( edges < 1 || edges > 9);

            for(i=0;i<edges;i++){
                printf("\nX%d: ",i);
                scanf("%f",&originalMatrix[i][0]);//a[0][0] = x1. a[1][0] = x2. a[2][0] = x3...
                printf("\nY%d: ",i);
                scanf("%f",&originalMatrix[i][1]);//a[0][1] = y1. a[1][1] = y2. a[2][1] = y3...
            }
        } else{

            //PENTAGONO
            edges = 5;
            originalMatrix[0][0] = 150;
            originalMatrix[0][1] = 150;
            originalMatrix[1][0] = 250;
            originalMatrix[1][1] = 150;
            originalMatrix[2][0] = 270;
            originalMatrix[2][1] = 250;
            originalMatrix[3][0] = 200;
            originalMatrix[3][1] = 300;
            originalMatrix[4][0] = 130;
            originalMatrix[4][1] = 250;
            /*
            //QUADRADO
            edges = 4;
            originalMatrix[0][0] = 150;
            originalMatrix[0][1] = 150;
            originalMatrix[1][0] = 250;
            originalMatrix[1][1] = 150;
            originalMatrix[2][0] = 250;
            originalMatrix[2][1] = 250;
            originalMatrix[3][0] = 150;
            originalMatrix[3][1] = 250;
            */
            /*
            //TRIANGULO
            edges = 3;
            originalMatrix[0][0] = 150;
            originalMatrix[0][1] = 150;
            originalMatrix[1][0] = 250;
            originalMatrix[1][1] = 150;
            originalMatrix[2][0] = 205;
            originalMatrix[2][1] = 250;
            */
        }
        originalMatrix[edges][0]=originalMatrix[0][0]; // Xaresta = X1
        originalMatrix[edges][1]=originalMatrix[0][1]; // Yaresta = X1

        while(reset == 0){
            printf("\nEscolha uma opção:\n");
            printf("\n1- Translacao\n2- Escala\n3- Rotacao\n4- Espelhamento\n5- Cisalhamento\n\n9- MATRIZ PERSONALIZADA\n0- SAIR\n\n");
            scanf("%d",&option);
            switch(option){
                case 0:
                    return 0;
                    break;
                case 1:
                    translation(originalMatrix);
                    break;
                case 2:
                    scale(originalMatrix);
                    break;
                case 3:
                    rotation(originalMatrix);
                    break;
                case 4:
                    mirroring(originalMatrix);
                    break;
                case 5:
                    shear(originalMatrix);
                    break;
                case 9:
                    for(i=0;i<edges+1;i++)
                    {
                        originalMatrix[i][0]=0;
                        originalMatrix[i][1]=0;
                    }
                    system("cls");
                    reset = 1;
                    custom = 1;
                    break;
            }
        }
    }while( true );
}


