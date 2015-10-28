
#include "Triangle.h"
#include "CastleEngine.h"

Triangle::Triangle() : DisplayableObject()
{
    
}

Triangle::~Triangle()
{
    
}

void Triangle::Draw()
{
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 0, 0);
    glVertex3d( -CastleEngine::GetWindowWidth()/3, -CastleEngine::GetWindowHeight()/4, -2.0 );
    glColor3f(0, 1.0, 0);
    glVertex3d(  CastleEngine::GetWindowWidth()/3, -CastleEngine::GetWindowHeight()/4, -2.0 );
    glColor3ub(0, 0, 255);
    glVertex3d( 0.0,  CastleEngine::GetWindowHeight()/3, -2.0 );
    glEnd();
}