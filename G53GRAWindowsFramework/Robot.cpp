//
//  Robot.cpp
//  G53GRAMacFramework
//
//  Created by mac on 21/02/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#include "Robot.h"
#include <cmath>

Robot :: Robot(float x, float y, float z, int direction):direction(direction),angle(0.0f),speed(0.05),t(0),day(1)
{
	position[0]=x;
	position[1]=y;
	position[2]=z;
	r=0.01 * (rand() % 100);  
	g=0.01 * (rand() % 100);  
	b=0.01 * (rand() % 100);  
}

Robot :: ~Robot()
{

}

void Robot::Update(const double &delytime)
{
	 if (day<360)
        day++;
    else
        day=0;

	if (angle >= 15 || angle <= -15)
		forward = !forward;

	if (forward)
		angle += 1;
	else
		angle -= 1;

	switch (direction) {
	case 0:
		position[2]+=speed;
		break;
	case 1:
		position[2]-=speed;
		break;
	case 2:
		position[0]+=speed;
		break;
	case 3:
		position[0]-=speed;
		break;

	default:
		break;
	}

	if(t > 100)
	{
		direction = rand() % 4;
		t = 0;
	}
	t++;
}

void Robot::Draw()
{
	DrawRobot(position[0], position[1], position[2]);
}

void Robot::DrawRobot(float x, float y, float z)
{
	glEnable(GL_LIGHTING);

	glPushMatrix();
	{
		glTranslatef(0,0.2,0);
		glTranslatef(x, y, z);
		glScaled(0.2, 0.2, 0.2);
		glTranslatef(0,5, 0);

		switch (direction) {
		case 1:
			glRotatef(180,0,1,0);
			break;
		case 2:
			glRotatef(90,0,1,0);
			break;
		case 3:
			position[0]-=speed;
			glRotatef(-90,0,1,0);
			break;

		default:
			break;
		}

		DrawHead();
		glTranslatef(0, -3.5, 0);
		DrawBody();

		//draw sun
		glPushMatrix();
		{

			glTranslatef(-2.0f, -0.5f, 0.0f);
			glTranslatef(0.0f, 2.0f, 0.0f);
			glRotatef(angle, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -2.0f, 0.0f);
			DrawArm();
		}
		glPopMatrix();

		//draw earth
		glPushMatrix();
		{
			glTranslatef(2.0f, -0.5f, 0.0f);
			glTranslatef(0.0f, 2.0f, 0.0f);
			glRotatef(-angle, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -2.0f, 0.0f);
			DrawArm();
		}
		glPopMatrix();


		//draw moon
		glPushMatrix();
		{

			glTranslatef(-1.0f, -5.0f, 0.0f);
			glTranslatef(0.0f, 2.5f, 0.0f);
			glRotatef(-angle, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -2.5f, 0.0f);

			DrawLeg();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(1.0f, -5.0f, 0.0f);
			glTranslatef(0.0f, 2.5f, 0.0f);
			glRotatef(angle, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -2.5f, 0.0f);
			DrawLeg();
		}
		glPopMatrix();

		glTranslatef(0.0f, 5.0f, -1.5f);
		DrawSun();
	}
	glPopMatrix();
	glDisable(GL_LIGHTING);
}


void Robot::DrawHead()
{
	glPushMatrix();

	/*      Sets color to white*/
	glColor3f(1.0f, 1.0f, 1.0f);

	/*      Creates 2 x 2 x 2 cube*/
	glScalef(2.0f, 2.0f, 2.0f);
	glutSolidCube(1);

	glPopMatrix();
}

void Robot::DrawBody()
{
	glPushMatrix();

	/*      Sets color to blue*/
	glColor3f(0.0f, 0.0f, 1.0f);

	/*      Creates 3 x 5 x 1 cube*/
	glScalef(3.0f, 5.0f, 1.0f);
	glutSolidCube(1);
	glPopMatrix();
}

void Robot::DrawArm()
{
	glPushMatrix();

	/*      Sets color to red*/
	glColor3f(1.0f, 0.0f, 0.0f);

	/*      Creates 1 x 4 x 1 cube*/
	glScalef(1.0f, 4.0f, 1.0f);
	glutSolidCube(1);

	glPopMatrix();
}

void Robot::DrawLeg()
{
	glPushMatrix();
	{
		/*      Sets color to yellow*/
		glColor3f(1.0f, 1.0f, 0.0f);

		/*      Creates 1 x 5 x 1 cube*/

		glPushMatrix();
		{
			glScalef(1.0f, 5.0f, 1.0f);
			glutSolidCube(1);
		}
		glPopMatrix();

		glTranslatef(0,-2,0.3);
		glScalef(1.0f, 1.0f, 1.5f);
		glutSolidCube(1);
	}
	glPopMatrix();

}

void Robot::DrawSun()
{
    glPushMatrix();
    {
		glScaled(0.1,0.1,0.1);
        glColor3f(r, g, b);
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
    
}