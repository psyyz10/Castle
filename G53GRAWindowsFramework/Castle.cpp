//
//  Castle.cpp
//  G53GRAMacFramework
//
//  Created by mac on 29/03/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#include "Castle.h"
#include "Engine.h"

Castle::Castle(float x, float y, float z,const std::string& filePath):day(1)
{
	position[0]=x;
	position[1]=y;
	position[2]=z;
	texId = Engine::GetTexture(filePath);
	texId2 = Engine::GetTexture("./window.bmp");
}

Castle::~Castle()
{

}

void Castle::Update(const double &deltatime)
{
	if (day<360)
		day++;
	else
		day=0;

}

void Castle::Draw()
{
	glEnable(GL_LIGHTING);      

	glColor3ub(0, 100, 0);
	glPushMatrix();
	{
		glTranslated(position[0],position[1]+4,position[2]);
		glScaled(20, 10, 20);
		DrawWall();

		glColor3ub(0, 100, 0);
		for(float i = -0.5; i <= 0.5; i += 0.5)
		{
			glPushMatrix();
			{
				glTranslated(i, 1, 1);
				glScaled(0.2, 0.15, 0.05);
				Draw3DBrick(1);
			}
			glPopMatrix();
		}

		for(float i = -0.5; i <= 0.5; i += 0.5)
		{
			glPushMatrix();
			{
				glTranslated(i, 1, -1);
				glScaled(0.2, 0.15, 0.05);
				Draw3DBrick(1);
			}
			glPopMatrix();
		}

		for(float i = -0.5; i <= 0.5; i += 0.5)
		{
			glPushMatrix();
			{
				glTranslated(1, 1, i);
				glRotatef(90,0,1,0);
				glScaled(0.2, 0.15, 0.05);
				Draw3DBrick(1);
			}
			glPopMatrix();
		}

		for(float i = -0.5; i <= 0.5; i += 0.5)
		{
			glPushMatrix();
			{
				glTranslated(-1, 1, i);
				glRotatef(90,0,1,0);
				glScaled(0.2, 0.15, 0.05);
				Draw3DBrick(1);
			}
			glPopMatrix();
		}

		//DrawClous();
		glPushMatrix();
		{
			glTranslated(0, 4, 1);
			DrawClouds();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(-0.9, 1.4, 0.9);
			glScaled(0.2, 1, 0.2);
			DrawHead();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(0.9, 1.4, 0.9);
			glScaled(0.2, 1, 0.2);
			DrawHead();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(-0.9, 1.4, -0.9);
			glScaled(0.2, 1, 0.2);
			DrawHead();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(0.9, 1.4, -0.9);
			glScaled(0.2, 1, 0.2);
			DrawHead();
		}
		glPopMatrix();

		glTranslated(0, 1, 0);

		glPushMatrix();
		{
			glScaled(1, 0.01, 1);
			Draw3DBrick(2);
		}
		glPopMatrix();

		glTranslated(0, 0.3, 0.5);

		glPushMatrix();
		{
			glTranslated(0, 0.2, 0.0);
			glScaled(0.7, 1.1, 0.7);
			DrawMainHead();
		}
		glPopMatrix();

		glTranslated(0, 1.4, 0);

		DrawFlage();

	}
	glPopMatrix();


	glDisable(GL_LIGHTING);
}

void Castle::DrawFlage()
{
	glPushMatrix();
	{

		glPushMatrix();
		{
			glColor3ub(110, 70, 40);
			glScalef(0.07,1.3,0.07);
			glutSolidCube(1);
		}
		glPopMatrix();

		glTranslated(0.15, 0.2, 0);

		glPushMatrix();
		{
			glPushMatrix();
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glScalef(0.2,0.6,0.05);
				glutSolidCube(1);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslated(0, 0, 0.01);
				glColor3f(1.0f, 1.0f, 0.0f);
				glScalef(0.2,0.15,0.05);
				glutSolidCube(1);
			}
			glPopMatrix();

			glPushMatrix();
			{

				glTranslated(0, 0, 0.01);
				glScalef(0.05,0.5,0.05);
				glColor3f(1.0f, 1.0f, 0.0f);
				glutSolidCube(1);
			}
			glPopMatrix();

		}
		glPopMatrix();

		glTranslated(0.15, 0.1, -0.02);

		glPushMatrix();
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glScalef(0.15,0.6,0.05);
			glutSolidCube(1);

			glPushMatrix();
			{

				glTranslated(0.3, 0, 0.01);
				glScalef(1.2,0.2,1);
				glColor3f(1.0f, 1.0f, 0.0f);
				glutSolidCube(1);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glTranslated(0.1, 0.1, -0.02);

		glPushMatrix();
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glScalef(0.1,0.4,0.05);
			glutSolidCube(1);
		}
		glPopMatrix();

		glTranslated(0.1, 0.1, -0.02);

		glPushMatrix();
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glScalef(0.1,0.2,0.05);
			glutSolidCube(1);
		}
		glPopMatrix();

	}
	glPopMatrix();
}

void Castle::DrawHead()
{
	glColor3ub(0, 100, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId);    // Tell openGL which texture buffer to apply as texture
	glColor3f(1.0, 1.0, 1.0);          // Set the base colour of the quad
	glPushMatrix();
	{
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluQuadricTexture(quadratic, GLU_TRUE);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glScaled(100, 2, 2);
		gluCylinder(quadratic,0.4f,0.4f,0.4f,32,32);
		glTranslated(0, 0, 0.4);
		DrawCircle(0.4,360);
	}
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0); // Bind to the blank buffer to stop ourselves accidentaly using the wrong texture in the next draw call
	glDisable(GL_TEXTURE_2D);	
	//glTranslatef(0, 0.2, 0);

	glPushMatrix();
	{
		//glColor3ub(0, 100, 0);
		glColor3f(0.4, 0.4, 0.4);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(0.6, 1.2, 32, 32);
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		DrawCircle(0.6,360);
		glColor3ub(0, 100, 0);
	}
	glPopMatrix();
}

void Castle::DrawMainHead()
{
	glColor3ub(0, 100, 0);

	glPushMatrix();
	{
		glScaled(1, 1.2, 1);
		Draw3DBrick(0.75);
	}
	glPopMatrix();


	glPushMatrix(); // draw window
	{
		glTranslated(0, -0.1, 0.4);
		//glColor3ub(10, 10, 10);
		glScaled(0.3, 0.35, 0.01); 

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texId2);    // Tell openGL which texture buffer to apply as texture
		glColor3f(1.0, 1.0, 1.0);          // Set the base colour of the quad

		//glutSolidCube(0.3);
		glBegin(GL_QUADS);
		glNormal3d(0, 0, 1);
		glTexCoord2d(0.38, 1);   // Texture coordinate index into the top left sprite coord
		glVertex3d(-1, 1, 0);
		glTexCoord2d(0.38, 0.4);   // Texture coordinate index into the bottom left sprite coord
		glVertex3d(-1, -1, 0);
		glTexCoord2d(0.62, 0.4);   // Texture coordinate index into the bottom right sprite coord
		glVertex3d(1, -1, 0);
		glTexCoord2d(0.62, 1);   // Texture coordinate index into the top right sprite coord
		glVertex3d(1, 1, 0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0); // Bind to the blank buffer to stop ourselves accidentaly using the wrong texture in the next draw call
		glDisable(GL_TEXTURE_2D);	
	}
	glPopMatrix();

	glColor3ub(0, 100, 0);
	glTranslated(0, 0.5, 0);


	glPushMatrix();
	{
		glScaled(1, 0.3, 1);
		Draw3DBrick(1);
	}
	glPopMatrix();

	glColor3ub(0, 100, 0);
	for(float i = -0.4; i <= 0.5; i += 0.4)
	{
		glPushMatrix();
		{
			glTranslated(i, 0.1, 0.5);
			glScaled(0.2, 0.5, 0.05);
			Draw3DBrick(1);
		}
		glPopMatrix();
	}

	for(float i = -0.4; i <= 0.5; i += 0.4)
	{
		glPushMatrix();
		{
			glTranslated(i, 0.1, 0.5);
			glScaled(0.2, 0.5, 0.05);
			Draw3DBrick(1);
		}
		glPopMatrix();
	}
	for(float i = -0.4; i <= 0.5; i += 0.4)
	{
		glPushMatrix();
		{
			glTranslated(0.5, 0.1, i);
			glRotatef(90,0,1,0);
			glScaled(0.2, 0.5, 0.05);
			Draw3DBrick(1);
		}
		glPopMatrix();
	}
	for(float i = -0.4; i <= 0.5; i += 0.4)
	{
		glPushMatrix();
		{
			glTranslated(-0.5, 0.1, i);
			glRotatef(90,0,1,0);
			glScaled(0.2, 0.5, 0.05);
			Draw3DBrick(1);
		}
		glPopMatrix();
	}

	glPushMatrix();
	{
		glTranslated(-0.5, 0.2, 0.5);
		glScaled(0.1, 0.7, 0.1);
		Draw3DBrick(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(-0.5, 0.2, -0.5);
		glScaled(0.1, 0.7, 0.1);
		Draw3DBrick(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0.5, 0.2, 0.5);
		glScaled(0.1, 0.7, 0.1);
		Draw3DBrick(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0.5, 0.2, -0.5);
		glScaled(0.1, 0.7, 0.1);
		Draw3DBrick(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0, 0.2, 0.5);
		glScaled(0.1, 0.7, 0.1);
		Draw3DBrick(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0, 0.2, -0.5);
		glScaled(0.1, 0.7, 0.1);
		Draw3DBrick(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0.5, 0.2, 0);
		glScaled(0.1, 0.7, 0.1);
		Draw3DBrick(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(-0.5, 0.2, 0);
		glScaled(0.1, 0.7, 0.1);
		Draw3DBrick(1);
	}
	glPopMatrix();


}

void Castle::DrawCircle(float r, int num_segments) 
{ 
	glBegin(GL_TRIANGLE_FAN);
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

		float x = r * cosf(theta);
		float y = r * sinf(theta);

		glVertex2f(x, y);

	} 
	glEnd(); 
}

void Castle:: DrawClouds()
{
	glPushMatrix();
	{
		glColor3f(128.0f, 128.0f, 128.0f);
		glScaled(.5, .1, .1);
		glutSolidCube(1);
		glTranslatef(0,1,0);
		glScaled(.7, 1, 1);
		glutSolidCube(1);
		glTranslatef(0,1,0);
		glScaled(.5, 1, 1);
		glutSolidCube(1);
	}
	glPopMatrix();

	glTranslatef(1,-0.2,-1);

	glPushMatrix();
	{
		glColor3f(128.0f, 128.0f, 128.0f);
		glScaled(.5, .1, .1);
		glutSolidCube(1);
		glTranslatef(0,1,0);
		glScaled(.7, 1, 1);
		glutSolidCube(1);
	}
	glPopMatrix();

	glTranslatef(-2,0.3,-1);

	glPushMatrix();
	{
		glColor3f(128.0f, 128.0f, 128.0f);
		glScaled(.5, .1, .1);
		glutSolidCube(1);
		glTranslatef(0,1,0);
		glScaled(.7, 1, 1);
		glutSolidCube(1);
		glTranslatef(0,1,0);
		glScaled(.5, 1, 1);
		glutSolidCube(1);
	}
	glPopMatrix();
}

void Castle::DrawWall()
{
	glPushMatrix();
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texId);    // Tell openGL which texture buffer to apply as texture
		glColor3f(1.0, 1.0, 1.0);          // Set the base colour of the quad
		glBegin(GL_QUADS);

		glNormal3d(0, 0, -1);
		glTexCoord2d(0, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(1, 1, -1);
		glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
		glVertex3d(1, -1, -1);
		glTexCoord2d(2, 0);   // Texture coordinate index into the bottom right sprite coord
		glVertex3d(-1, -1, -1);
		glTexCoord2d(2, 2);   // Texture coordinate index into the top right sprite coord
		glVertex3d(-1, 1, -1);

		glNormal3d(1, 0, 0);
		glTexCoord2d(0, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(1, 1, 1);
		glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
		glVertex3d(1, -1, 1);
		glTexCoord2d(2, 0);   // Texture coordinate index into the bottom right sprite coord
		glVertex3d(1, -1, -1);
		glTexCoord2d(2, 2);   // Texture coordinate index into the top right sprite coord
		glVertex3d(1, 1, -1);

		glNormal3d(-1, 0, 0);
		glTexCoord2d(0, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(-1, 1, -1);
		glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
		glVertex3d(-1, -1, -1);
		glTexCoord2d(2, 0);   // Texture coordinate index into the bottom right sprite coord
		glVertex3d(-1, -1, 1);
		glTexCoord2d(2, 2);   // Texture coordinate index into the top right sprite coord
		glVertex3d(-1, 1, 1);

		glNormal3d(0, 0, 1);
		glTexCoord2d(0, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(-1, 1, 1);
		glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
		glVertex3d(-1, -1, 1);
		glTexCoord2d(0.8, 0);   // Texture coordinate index into the bottom right sprite coord
		glVertex3d(-0.2, -1, 1);
		glTexCoord2d(0.8, 2);   // Texture coordinate index into the top right sprite coord
		glVertex3d(-0.2, 1, 1);

		glNormal3d(0, 0, 1);
		glTexCoord2d(0, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(0.2, 1, 1);
		glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
		glVertex3d(0.2, -1, 1);
		glTexCoord2d(0.8, 0);   // Texture coordinate index into the bottom right sprite coord
		glVertex3d(1, -1, 1);
		glTexCoord2d(0.8, 2);   // Texture coordinate index into the top right sprite coord
		glVertex3d(1, 1, 1);

		glNormal3d(0, 0, 1);
		glTexCoord2d(0.8, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(-0.2, 1, 1);
		glTexCoord2d(0.8, 1.2);   // Texture coordinate index into the bottom left sprite coord
		glVertex3d(-0.2, 0.2, 1);
		glTexCoord2d(0.9, 1.5);   // Texture coordinate index into the bottom right sprite coord
		glVertex3d(-0.1, 0.5, 1);
		glTexCoord2d(0.9, 2);   // Texture coordinate index into the top right sprite coord
		glVertex3d(-0.1, 1, 1);

		glNormal3d(0, 0, 1);
		glTexCoord2d(0.9, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(-0.1, 1, 1);
		glTexCoord2d(0.9, 1.5);   // Texture coordinate index into the top left sprite coord
		glVertex3d(-0.1, 0.5, 1);
		glTexCoord2d(1.1, 1.5);   // Texture coordinate index into the top left sprite coord
		glVertex3d(0.1, 0.5, 1);
		glTexCoord2d(1.1, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(0.1, 1, 1);

		glNormal3d(0, 0, 1);
		glTexCoord2d(1.1, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(0.1, 1, 1);
		glTexCoord2d(1.1, 1.5);   // Texture coordinate index into the top left sprite coord
		glVertex3d(0.1, 0.5, 1);
		glTexCoord2d(1.2, 1.2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(0.2, 0.2, 1);
		glTexCoord2d(1.2, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(0.2, 1, 1);

		/*
		glNormal3d(0, 1, 0);
		glVertex3d(-1, 1, -1);
		glVertex3d(-1, 1, 1);
		glVertex3d(1, 1, 1);
		glVertex3d(1, 1, -1);
		*/

		glNormal3d(0, 0, -1);
		glTexCoord2d(0, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(-0.2, 1, 0.9);
		glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
		glVertex3d(-0.2, -1, 0.9);
		glTexCoord2d(2, 0);   // Texture coordinate index into the bottom right sprite coord
		glVertex3d(-1, -1, 0.9);
		glTexCoord2d(2, 2);   // Texture coordinate index into the top right sprite coord
		glVertex3d(-1, 1, 0.9);

		glNormal3d(0, 0, -1);
		glTexCoord2d(0, 2);   // Texture coordinate index into the top left sprite coord
		glVertex3d(1, 1, 0.9);
		glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
		glVertex3d(1, -1, 0.9);
		glTexCoord2d(2, 0);   // Texture coordinate index into the bottom right sprite coord
		glVertex3d(0.2, -1, 0.9);
		glTexCoord2d(2, 2);   // Texture coordinate index into the top right sprite coord
		glVertex3d(0.2, 1, 0.9);

		glNormal3d(1, 0, 0);
		glVertex3d(-0.9, 1, 1);
		glVertex3d(-0.9, -1, 1);
		glVertex3d(-0.9, -1, -1);
		glVertex3d(-0.9, 1, -1);

		glNormal3d(-1, 0, 0);
		glVertex3d(0.9, 1, -1);
		glVertex3d(0.9, -1, -1);
		glVertex3d(0.9, -1, 1);
		glVertex3d(0.9, 1, 1);

		glNormal3d(0, 0, 1);
		glVertex3d(-1, 1, -0.9);
		glVertex3d(-1, -1, -0.9);
		glVertex3d(1, -1, -0.9);
		glVertex3d(1, 1, -0.9);


		glNormal3d(1, 0, 0);
		glVertex3d(-0.2, 0.2, 1);
		glVertex3d(-0.2, -1, 1);
		glVertex3d(-0.2, -1, 0.9);
		glVertex3d(-0.2, 0.2, 0.9);

		glNormal3d(-1, 0, 0);
		glVertex3d(0.2, 0.2, 0.9);
		glVertex3d(0.2, -1, 0.9);
		glVertex3d(0.2, -1, 1);
		glVertex3d(0.2, 0.2, 1);

		glNormal3d(0, 0, -1);
		glVertex3d(-0.1, 1, 0.9);
		glVertex3d(-0.1, 0.5, 0.9);
		glVertex3d(-0.2, 0.2, 0.9);
		glVertex3d(-0.2, 1, 0.9);

		glNormal3d(0, 0, -1);
		glVertex3d(0.1, 1, 0.9);
		glVertex3d(0.1, 0.5, 0.9);
		glVertex3d(-0.1, 0.5, 0.9);
		glVertex3d(-0.1, 1, 0.9);

		glNormal3d(0, 0, -1);	
		glVertex3d(0.2, 1, 0.9);
		glVertex3d(0.2, 0.2, 0.9);
		glVertex3d(0.1, 0.5, 0.9);
		glVertex3d(0.1, 1, 0.9);

		glNormal3d(0, -1, 0);	
		glVertex3d(-0.1, 0.5, 0.9);
		glVertex3d(0.1, 0.5, 0.9);
		glVertex3d(0.1, 0.5, 1);
		glVertex3d(-0.1, 0.5, 1);

		glVertex3d(0.1, 0.5, 1);
		glVertex3d(0.1, 0.5, 0.9);
		glVertex3d(0.2, 0.2, 0.9);
		glVertex3d(0.2, 0.2, 1);

		glVertex3d(-0.2, 0.2, 1);
		glVertex3d(-0.2, 0.2, 0.9);
		glVertex3d(-0.1, 0.5, 0.9);
		glVertex3d(-0.1, 0.5, 1);

		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0); // Bind to the blank buffer to stop ourselves accidentaly using the wrong texture in the next draw call
		glDisable(GL_TEXTURE_2D);	
	}
	glPopMatrix();
}

void Castle:: Draw3DBrick(GLfloat size)
{   
	size *= 0.5;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId);    // Tell openGL which texture buffer to apply as texture
	glColor3f(1.0, 1.0, 1.0);          // Set the base colour of the quad

	glBegin(GL_QUADS);

	glNormal3d(0, 0, 1);
	glTexCoord2d(0, 1);   // Texture coordinate index into the top left sprite coord
	glVertex3d(-size, size, size);
	glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
	glVertex3d(-size, -size, size);
	glTexCoord2d(0.5, 0);   // Texture coordinate index into the bottom right sprite coord
	glVertex3d(size, -size, size);
	glTexCoord2d(0.5, 1);   // Texture coordinate index into the top right sprite coord
	glVertex3d(size, size, size);

	glNormal3d(0, 0, -1);
	glTexCoord2d(0, 0.5);   // Texture coordinate index into the top left sprite coord
	glVertex3d(size, size, -size);
	glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
	glVertex3d(size, -size, -size);
	glTexCoord2d(0.5, 0);   // Texture coordinate index into the bottom right sprite coord
	glVertex3d(-size, -size, -size);
	glTexCoord2d(0.5, 0.5);   // Texture coordinate index into the top right sprite coord
	glVertex3d(-size, size, -size);

	glNormal3d(1, 0, 0);
	glTexCoord2d(0, 0.5);   // Texture coordinate index into the top left sprite coord
	glVertex3d(size, size, size);
	glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
	glVertex3d(size, -size, size);
	glTexCoord2d(0.5, 0);   // Texture coordinate index into the bottom right sprite coord
	glVertex3d(size, -size, -size);
	glTexCoord2d(0.5, 0.5);   // Texture coordinate index into the top right sprite coord
	glVertex3d(size, size, -size);

	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0.5);   // Texture coordinate index into the top left sprite coord
	glVertex3d(-size, size, -size);
	glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
	glVertex3d(-size, -size, -size);
	glTexCoord2d(0.5, 0);   // Texture coordinate index into the bottom right sprite coord
	glVertex3d(-size, -size, size);
	glTexCoord2d(0.5, 0.5);   // Texture coordinate index into the top right sprite coord
	glVertex3d(-size, size, size);

	glNormal3d(0, 1, 0);
	glTexCoord2d(0, 0.5);   // Texture coordinate index into the top left sprite coord
	glVertex3d(-size, size, -size);
	glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
	glVertex3d(-size, size, size);
	glTexCoord2d(0.5, 0);   // Texture coordinate index into the bottom right sprite coord
	glVertex3d(size, size, size);
	glTexCoord2d(0.5, 0.5);   // Texture coordinate index into the top right sprite coord
	glVertex3d(size, size, -size);

	glNormal3d(0, -1, 0);
	glTexCoord2d(0, 0.5);   // Texture coordinate index into the top left sprite coord
	glVertex3d(-size, -size, size);
	glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
	glVertex3d(-size, -size, -size);
	glTexCoord2d(0.5, 0);   // Texture coordinate index into the bottom right sprite coord
	glVertex3d(size, -size, -size);
	glTexCoord2d(0.5, 0.5);   // Texture coordinate index into the top right sprite coord
	glVertex3d(size, -size, size);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0); // Bind to the blank buffer to stop ourselves accidentaly using the wrong texture in the next draw call
	glDisable(GL_TEXTURE_2D);	
}