//
// Created by augustochaves on 27/06/16.
//


#include <tgmath.h>
#include <iostream>
#include <fstream>
#include "ps.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <vector>

std::string strVS = "#version 330 core\
in vec3 aVel;\
in vec3 aVert;\
in float aTime0;\
in vec2 aTexCoord;\
uniform mat4 uMVMatrix;\
uniform mat4 uPMatrix;\
uniform mat4 bMatrix;\
uniform float uTime;\
uniform float uLifeTime;\
uniform vec4 uColor;\
uniform vec3 uPos;\
out vec4 vCol;\
out vec2 vTexCoord;\
void main() {\
    // set position\
    float dt = uTime - aTime0;\
    float alpha = clamp(1.0 - 2.0*dt/uLifeTime, 0.0, 1.0);\
    if(dt < 0.0 || dt > uLifeTime || alpha < 0.01) {\
        // out of sight!\
        gl_Position = vec4(0.0, 0.0, -1000.0, 1.0);\
    }\
    else {\
        // calculate new position\
        vec3 accel = vec3(0.0, 0.0, -9.8);\
        // apply a twist\
        float PI = 3.14159265358979323846264;\
        float theta = mod(100.0*length(aVel)*dt, 360.0)*PI/180.0;\
        mat4 rot =  mat4(\
                vec4(cos(theta),  sin(theta), 0.0, 0.0),\
                vec4(-sin(theta),  cos(theta), 0.0, 0.0),\
                vec4(0.0,                 0.0, 1.0, 0.0),\
                vec4(0.0,         0.0,         0.0, 1.0)\
        );\
        // apply billboard matrix\
        vec4 pos2 =  bMatrix*rot*vec4(aVert, 1.0);\
        // calculate position\
        vec3 newPos = pos2.xyz + uPos + aVel*dt + 0.5*accel*dt*dt;\
        // apply transformations\
        gl_Position = uPMatrix * uMVMatrix * vec4(newPos, 1.0);\
    }\
    // set color\
    vCol = vec4(uColor.rgb, alpha);\
    // set tex coords\
    vTexCoord = aTexCoord;\
}\
";

std::string strFS = "#version 330 core\
uniform sampler2D uSampler;\
in vec4 vCol;\
in vec2 vTexCoord;\
out vec4 fragColor;\
void main() {\
    // get texture color\
    vec4 texCol = texture(uSampler, vec2(vTexCoord.s, vTexCoord.t));\
    // multiple by set vertex color, use vertex color alpha\
    fragColor = vec4(texCol.rgb*vCol.rgb, vCol.a);\
}\
";

class Camera{
    Camera(double eye[], double center[], double up[]){
        this->r = 10.00;
        this->theta = 0;
        this->eye = eye;
        this->center = center;
        this->up = up;
    };

public:
    double * eye;
    double * center;
    double * up;

public:
    double r;
    int theta;

    void Rotate();


};
double getRadians(int degrees){
    return degrees *(M_PI/180);
};

void Camera::Rotate(){
    this->theta = (this->theta +1) % 360;
    //this->eye = this->center + [this->r* cos(getRadians(this->theta)), this->r * sin(getRadians(this->theta))];
};

GLuint LoadTexture( const char * filename ) {

    GLuint texture;

    int width, height;

    unsigned char *data;

    FILE *file;

    file = fopen(filename, "rb");

    if (file == NULL) return 0;
    width = 1024;
    height = 512;
    data = (unsigned char *) malloc(width * height * 3);
    //int size = fseek(file,);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    for (int i = 0; i < width * height; ++i) {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;

    }


    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

};




std::string readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}


GLuint LoadShader(const char *vertex_path, const char *fragment_path) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shaders
    std::string vertShaderStr = readFile(vertex_path);
    std::string fragShaderStr = readFile(fragment_path);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader
    std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // Check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    // Compile fragment shader
    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // Check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    std::cout << &fragShaderError[0] << std::endl;

    std::cout << "Linking program" << std::endl;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}

class ParticleSystem{
    ParticleSystem(int nump){
        this->nump = nump;
        this->t = 0.0;
        this->lifeTime = 5.0;
        this->startPos = {0.0, 0.0, 0.5};
        this->texture = LoadTexture("star.png");

        this->program = LoadShader(strVS.c_str(), strFS.c_str());

        glUseProgram(this->program);

        texLoc = __glewGetUniformLocation(this->program, "uTex");

        glUniform1i(texLoc, 0);

        this->timeU = __glewGetUniformLocation(this->program, "uTime");
        this->lifeTimeU = __glewGetUniformLocation(this->program, "uLifeTime");
        this->pMatrixUniform = __glewGetUniformLocation(this->program, "uPMatrix");
        this->mvMatrixUniform = glGetUniformLocation(this->.program, "uMVMatrix");
        this->colorU = __glewGetUniformLocation(this->program, "uColor");
        this->samplerU = __glewGetUniformLocation(this->program, "uSampler");
        this->posU = __glewGetUniformLocation(this->program, "uPos");

        this->vertIndex = __glewGetAttribLocation(this->program, "aVert");
        this->texIndex = __glewGetAttribLocation(this->program, "aTexCoord");
        this->time0Index = __glewGetAttribLocation(this->program, "aTime0");
        this->velIndex = __glewGetAttribLocation(this->program, "aVel");

        this->enableBillboard = true;
        this->disableDepthMask = true;
        this->enableBlend = true;



    };

public:
    double lifeTime;



    double t;
    double startPos[];
    GLuint texture;
    GLuint program;
    GLuint texLoc;
    GLuint timeU;
    GLuint lifeTimeU;
    GLuint pMatrixUniform;
    GLuint mvMatrixUniform;
    GLuint colorU;
    GLuint bMatrixU;
    GLuint samplerU;
    GLuint posU;
    GLuint vertIndex;
    GLuint texIndex;
    GLuint time0Index;
    GLuint velIndex;

    bool enableBillboard;
    bool disableDepthMask;
    bool enableBlend;

    bool useStarTexture;


private:
    int nump;


};


