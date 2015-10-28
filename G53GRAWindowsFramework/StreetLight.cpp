#include "StreetLight.h"

StreetLight::StreetLight(Camera* c,float x, float y, float z,int num,int direction):cam(c),num(num),direction(direction)
{
	position[0]=x;
	position[1]=y;
	position[2]=z;

	lightposition[0] = x; 
    lightposition[1] = y+3.2; 
    lightposition[2] = z;
    lightposition[3] = 1.0;

	ambient[0] = 0.1;  // Set the ambient colour of the light
    ambient[1] = 0.1;
    ambient[2] = 0.1;
    ambient[3] = 1.0;
    
    diffuse[0] = 1;   // Set the diffuse colour of the light
    diffuse[1] = 1;
    diffuse[2] = 0.4;
    diffuse[3] = 1.0;
    
    specular[0] = 1.0;  // Set the specular colour of the light
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;

}


StreetLight::~StreetLight(void)
{
}

void StreetLight::Draw()
{
	glPushMatrix();
	{
		if (direction == 0)
			lightposition[0] =position[0] + 1.15;
		else if(direction == 1)
			lightposition[0] = position[0]-1.15;
		//add light
		glPushMatrix();
		{
			glDisable(GL_LIGHTING);
			glTranslatef(lightposition[0], lightposition[1], lightposition[2]);
			glColor4fv(diffuse);
			glutSolidSphere(0.2,32, 32);
			glEnable(GL_LIGHTING);
		}
		glPopMatrix();

		glColor3ub(0, 100, 0);
		glTranslated(position[0],position[1],position[2]);
		glScaled(1, 1, 1);

		if (direction == 0)
			glRotatef(90,0,1,0);
		else if(direction == 1)
			glRotatef(-90,0,1,0);

		//add arm
		glPushMatrix();
		{
			glTranslatef(0,0.5,0);

			//add arm 1
			glPushMatrix();
			{
				glScaled(1,1.5,1);
				DrawArm();
			}
			glPopMatrix();

			glTranslatef(0,1.5,0);

			//add arm 2
			glPushMatrix();
			{
				glScaled(0.7,1.5,0.7);
				DrawArm();
			}
			glPopMatrix();

			//glTranslatef(0,1,0);

			//add arm 3
			glPushMatrix();
			{
				glRotatef(35,1,0,0);
				glTranslatef(0,1.5,0);

				glPushMatrix();
				{
					glScaled(0.5,1.5,0.5);
					DrawArm();
				}
				glPopMatrix();
				glRotatef(-35,1,0,0);
				glTranslatef(0,-0.05,0.3);
				DrawHead();// add head
			}
			glPopMatrix();


		}
		glPopMatrix();
	}
	glPopMatrix();
	glDisable(GL_LIGHTING);
}

//draw head
void StreetLight::DrawHead()
{
	glPushMatrix();

	glScaled(0.3, 0.3, 0.3);

	double clipEq[4] = {0,1,0,-0.2};
	
	glPushMatrix();
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, clipEq);
	glutSolidSphere(1,32, 32);
	glDisable(GL_CLIP_PLANE0);

	glPopMatrix();


	glPopMatrix();
}

//draw arm
void StreetLight::DrawArm()
{
	glPushMatrix();
	{
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		//gluQuadricNormals(quadratic, GLU_SMOOTH);
		//gluQuadricTexture(quadratic, GLU_TRUE);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glScaled(100, 2, 2);
		gluCylinder(quadratic,0.1f,0.1f,1.0f,32,32);
		//glTranslated(0, 0, 0.4);
		//DrawCircle(0.4,360);
		gluQuadricNormals(quadratic, GLU_SMOOTH);
        gluQuadricTexture(quadratic, GLU_TRUE);
	}
	glPopMatrix();
}

void StreetLight::Update(const double &deltatime)
{

	glEnable(GL_LIGHTING);      // turn lighting on
    
    glLightfv(GL_LIGHT0+num, GL_AMBIENT, ambient);  // pass openGL the lighting model parameters for the Phong reflection model
    glLightfv(GL_LIGHT0+num, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0+num, GL_SPECULAR, specular);
    glLightf(GL_LIGHT0+num, GL_LINEAR_ATTENUATION, 0.05);   // Set the lights attentuation i.e. how quickly the light fades as we move away
    
	if(num == 0 )
		cam->SetUpCamera();
	
    glLightfv(GL_LIGHT0+num, GL_POSITION, lightposition);
    
    glEnable(GL_LIGHT0+num);
    
}
