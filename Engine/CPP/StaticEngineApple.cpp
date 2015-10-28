
#include "StaticEngineApple.h"

#include <stdio.h>

StaticEngineApple *StaticEngineApple::current = 0;
const char* StaticEngineApple::windowTitle = "";
int StaticEngineApple::windowID = 0;
int StaticEngineApple::windowWidth = 1;
int StaticEngineApple::windowHeight = 1;
int StaticEngineApple::time = 0;

StaticEngineApple::StaticEngineApple(int argc, char **argv, const char *title, const int& windowWidth, const int& windowHeight)
{
    StaticEngineApple::windowTitle = title;
    StaticEngineApple::windowWidth = windowWidth;
    StaticEngineApple::windowHeight = windowHeight;
    
    //Initialize GLUT
    glutInit(&argc, argv);
}

StaticEngineApple::~StaticEngineApple()
{
}

void StaticEngineApple::Run()
{
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100,100);
    windowID = glutCreateWindow(windowTitle);
    current = this;
    
    glutDisplayFunc(DrawFunc);
    glutReshapeFunc(ResizeFunc);
    glutKeyboardFunc(KeyDownFunc);
    glutKeyboardUpFunc(KeyUpFunc);
    glutSpecialFunc(SpecialKeyDownFunc);
    glutSpecialFunc(SpecialKeyUpFunc);
    glutMouseFunc(MouseFunc);
    glutMotionFunc(MouseMotionFunc);
    glutIdleFunc(IdleFunc);
    
    printf("Running OpenGL Version: %s\n", glGetString(GL_VERSION));
    
    InitFunc();
    
    glutMainLoop();
}

StaticEngineApple* StaticEngineApple::GetCurrentInstance()
{
    return StaticEngineApple::current;
}

const char* StaticEngineApple::GetWindowTitle()
{
    return StaticEngineApple::windowTitle;
}

int StaticEngineApple::GetWindowID()
{
    return StaticEngineApple::windowID;
}

int StaticEngineApple::GetWindowWidth()
{
    return StaticEngineApple::windowWidth;
}

int StaticEngineApple::GetWindowHeight()
{
    return StaticEngineApple::windowHeight;
}

void StaticEngineApple::InitFunc()
{
    // set background colour
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    
    // enable depth tests less than or equal
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    // enable culling of backface polygons
    glEnable(GL_CULL_FACE);
    
    // enable transparancy blending
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // enable 2D texturing
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    
    // turn off 2 sided lighting
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    
    // set the ambient light model
    GLfloat global_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    // enable directional light lighting
    // (x, y, z, 0.0) -> directional lighting
    // (x, y, z, 1.0) -> positional lighting
    glEnable(GL_LIGHTING);
    GLfloat ambience[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);
    
    // enable smooth shading from lighting
    glShadeModel(GL_SMOOTH);
    
    // enable automatic normalisation of normal vectors
    glEnable(GL_NORMALIZE);    
    
    current->Init();
    time = 0;
}

void StaticEngineApple::DrawFunc()
{    
    current->DrawScene();
	glutSwapBuffers();
}

void StaticEngineApple::ResizeFunc(int w, int h)
{
    StaticEngineApple::windowWidth = w;
    StaticEngineApple::windowHeight = h;
    current->HandleResize(w,h);
}

void StaticEngineApple::KeyDownFunc(unsigned char key, int x, int y)
{
    current->HandleKey(key, 1, x, y);
}

void StaticEngineApple::KeyUpFunc(unsigned char key, int x, int y)
{
    current->HandleKey(key, 0, x, y);
}

void StaticEngineApple::SpecialKeyDownFunc(int key, int x, int y)
{
    if( key>=1 && key<=12){
        current->HandleKey(key + 255, 1, x, y);
    } else {
        current->HandleKey(key+ 168, 1, x, y);
    }
}

void StaticEngineApple::SpecialKeyUpFunc(int key, int x, int y)
{
    if( key>=1 && key<=12){
        current->HandleKey(key + 255, 0, x, y);
    } else {
        current->HandleKey(key+ 168, 0, x, y);
    }
}

void StaticEngineApple::MouseFunc(int button, int state, int x, int y)
{
    current->Mouse(button, state, x, y);
}

void StaticEngineApple::MouseMotionFunc(int x, int y)
{
    current->MouseMotion(x, y);
}

void StaticEngineApple::IdleFunc()
{
    int t = glutGet(GLUT_ELAPSED_TIME);
    double diff = (double)(t - time) / 1000.0;
    time = t;
    
    current->Update(diff);
    
    glutPostRedisplay();
}

int StaticEngineApple::CheckGLError()
{
    int e=0;
    GLenum error = glGetError();
    while ( GL_NO_ERROR != error )
    {
        e++;
        printf("GL Error %i: %s\n", e, gluErrorString(error));
        error = glGetError();
    }
    
    return e;
}
