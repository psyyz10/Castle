//
//  Sun.cpp
//  G53GRAMacFramework
//
//  Created by mac on 31/03/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#include "Sun.h"


Sun::Sun(float x, float y, float z):day(1)
{
    position[0]=x;
    position[1]=y;
    position[2]=z;
	position[3] = 0.0; 

    ambient[0] = 0.3;  // Set the ambient colour of the light
    ambient[1] = 0.3;
    ambient[2] = 0.3;
    ambient[3] = 1.0;
    
    diffuse[0] = 1.0;   // Set the diffuse colour of the light
    diffuse[1] = 1.0;
    diffuse[2] = 1.0;
    diffuse[3] = 1.0;
    
    specular[0] = 1.0;  // Set the specular colour of the light
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;
}

Sun::~Sun()
{
    
}

void Sun::Update(const double &deltatime)
{
    if (day<360)
        day++;
    else
        day=0;
    
}

void Sun::Draw()
{
    glEnable(GL_LIGHTING);
    glPushMatrix();
    {
		
        glTranslatef(position[0],position[1],position[2]);
		glScaled(0.1,0.1,0.1);
        glColor3f(0.8f, 0, 0);
        glutSolidSphere(10.0, 40, 32);

        glColor3f(0.0f, 0.0f, 1.0f);
        glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
        glTranslatef(14, 0.0f, 0.0f);
        glutSolidSphere(4, 20, 20);

        glColor3f(1.0f, 1.0f, 0.0f);
        glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
        glTranslatef(8, 0.0f, 0.0f);
        glutSolidSphere(2, 20, 20);
        
    }
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
    
}