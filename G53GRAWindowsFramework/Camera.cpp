//
//  Camera.cpp
//  G53GRAMacFramework
//
//  Created by mac on 28/02/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#include "Camera.h"
#define GRAVITY -9.81;


Camera::Camera():rotation(0),wkey(false),skey(false),akey(false),dkey(false),fkey(false),gkey(false),jumpAnimation(0),jumpTranslation(0), jump(0), lMouse(false),speed(10)
{
	viewDirection[0] = 0;
	viewDirection[1] = 0;
	viewDirection[2] = -1;

	upDirection[0] = 0;
	upDirection[1] = 1;
	upDirection[2] = 0;

	position[0] = 0;
	position[1] = 0.5;
	position[2] = 5.0;

    cross(viewDirection, upDirection, rightDirection);
}

Camera::~Camera()
{
    
}

void Camera::Update(const double &deltaTime)
{
    if (wkey)
    {
        position[0] += speed * viewDirection[0] * deltaTime;
        position[2] += speed * viewDirection[2] * deltaTime;
    }
    if (skey)
    {
        position[0] -= speed * viewDirection[0] * deltaTime;
        position[2] -= speed * viewDirection[2] * deltaTime;
    }
    if (akey)
    {
        position[0] -=  speed * rightDirection[0] * deltaTime;
        position[2] -=  speed * rightDirection[2] * deltaTime;
    }
    if (dkey)
    {
        position[0] +=  speed * rightDirection[0] * deltaTime;
        position[2] +=  speed * rightDirection[2] * deltaTime;
    }
	if (fkey)
    {
        position[1] +=  speed * deltaTime;
    }
	if (gkey)
    {
        position[1] -=  speed * deltaTime;
    }
    if (jump) {
        Jump(deltaTime);
    }
}

void Camera::SetUpCamera()
{
    gluLookAt(position[0], position[1], position[2],
              position[0]+viewDirection[0], position[1]+viewDirection[1], position[2]+viewDirection[2],
              upDirection[0], upDirection[1], upDirection[2]);
}

void Camera::HandleKey(int key, int state, int x, int y)
{
    switch (key) {
        case 'w':
            if (!state && wkey) wkey = false;
            else if (state && !wkey) wkey = true;
            break;
        case 's':
            if (!state && skey) skey = false;
            else if (state && !skey) skey = true;
            break;
        case 'a':
            if (!state && akey) akey = false;
            else if (state && !akey) akey = true;
            break;
        case 'd':
            if (!state && dkey) dkey = false;
            else if (state && !dkey) dkey = true;
            break;
		case 'f':
			if (!state && fkey) fkey = false;
            else if (state && !fkey) fkey = true;
            break;
		case 'g':
			if (!state && gkey) gkey = false;
            else if (state && !gkey) gkey = true;
            break;
        case ' ':
            if (state && ~jump) jump = true;
            break;
        default:
            break;
    }
}

void Camera::HandleMouseMotion( int x, int y )
{

    scale(rightDirection, 0.005 * (x - px));
    //scale(rightDirection, 0.00005 * (x - px));
    add(viewDirection, rightDirection);
    norm(viewDirection);
    cross(viewDirection, upDirection, rightDirection);
    rightDirection[1]=0;
    norm(rightDirection);
    scale(upDirection, 0.005 * (py - y));
    add(viewDirection, upDirection);
    norm(viewDirection);
    cross(rightDirection, viewDirection, upDirection);
    
    px = x; py=y;
}

void Camera::HandleMouseClick( int button, int state, int x, int y )
{
    if(button == GLUT_LEFT_BUTTON && state && lMouse == false)
    {
        px = x; py = y;
        lMouse = true;
    }
    else if(button == GLUT_LEFT_BUTTON && !state && lMouse)
    {
        lMouse = false;
    }
    
}

void Camera::SetProjection()
{   glMatrixMode(GL_PROJECTION);                                    // ensure we apply the projection matrix to the GL_PROJECTION stack NOT the GL_MODELVIEW stack
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);  
}

void Camera::Jump(const double &deltaTime)
{
    jumpAnimation += deltaTime;
    
    if (jumpAnimation < 1) {
        jumpTranslation = 0.5*2*9.81*jumpAnimation + 0.5*2*jumpAnimation*jumpAnimation*GRAVITY;
    }
    else if (jumpAnimation > 1){
        jumpAnimation = 0;
        jump = false;
    }
    
    position[1] = jumpTranslation;
}

float* Camera::GetViewDirection( ) 
{
	float* pointer;
	pointer = viewDirection;
    // return the view direction coordinate based on the passed value
    return pointer;
}