//
//  Tree.cpp
//  G53GRAMacFramework
//
//  Created by mac on 14/03/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#include "Tree.h"

Tree::Tree(float x, float y, float z)
{
    position[0]=x;
    position[1]=y;
    position[2]=z;
    
}

Tree ::~Tree()
{
    
}

void Tree::Update(const double &deltatime)
{
    
}

void Tree::Draw()
{
    
    glEnable(GL_LIGHTING);
    glPushMatrix();
    {
        glTranslatef(position[0],position[1],position[2]);
        //glutSolidSphere(3, 10, 1);
        
        glPushMatrix();
        {
            GLUquadricObj *quadratic;
            quadratic = gluNewQuadric();
            gluQuadricNormals(quadratic, GLU_SMOOTH);
            gluQuadricTexture(quadratic, GLU_TRUE);
			
            glTranslatef(0, 0.4, 0);
            
            glPushMatrix();
            {
				//glColor3f(0.5f, 0.35f, 0.05f);
				glColor3ub(139, 90, 43);
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                //glScaled(100, 2, 2);
                gluCylinder(quadratic,0.2f,1.5f,10.0f,32,32);
            }
            glPopMatrix();
            
            glTranslatef(0, -0.1, 0);
            
            glPushMatrix();
            {
				glColor3ub(0, 100, 0);
                glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                glutSolidCone(0.8, 1.7, 32, 32);
            }
            glPopMatrix();
            
            glTranslatef(0, 0.5, 0);
            
            glPushMatrix();
            {
                glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                glutSolidCone(0.7, 1.2, 32, 32);
            }
            glPopMatrix();
            
            glTranslatef(0, 0.4, 0);
            
            glPushMatrix();
            {
                glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                glutSolidCone(0.6, 1.0, 32, 32);
            }
            glPopMatrix();

            
        }
        glPopMatrix();
    }
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
    
}