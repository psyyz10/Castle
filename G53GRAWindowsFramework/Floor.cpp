#include "Floor.h"
#include "Engine.h"

#define NUM_PATCHES 100
#define PATCH_SIZE 2.0f
using namespace std;

Floor::Floor( const int& gridX, const int& gridY, const float& xPos, const float& yPos, const float& zPos, const float& scale, const string& filePath ): xGridDims(gridX), yGridDims(gridY), time(0.0), frozen(false), scale(scale), floorDepth(-1.0)
{
	// This function will load in any power of 2 bitmapped image into openGL and return you the buffer id that it read it into
	texId = Engine::GetTexture(filePath);

	// initialise the grids texture coordinate memory we will need enough memory for both the s and t coordinate at each mesh vertex
	//texCoords = new float[(xGridDims+1) * (yGridDims+1) * 2];


	location[0] = xPos; // store the location of the grid in world space
	location[1] = yPos;
	location[2] = zPos;


	matAmbient[0] = 0.3f;   // set the material properties of the grid
	matAmbient[1] = 0.3f;
	matAmbient[2] = 0.3f;
	matAmbient[3] = 1.0f;

	matDiffuse[0] = 0.3f;
	matDiffuse[1] = 0.3f;
	matDiffuse[2] = 0.3f;
	matDiffuse[3] = 0.3f;

	matSpecular[0] = 0.0f;
	matSpecular[1] = 0.0f;
	matSpecular[2] = 0.0f;
	matSpecular[3] = 1.0f;

	matShininess = 0;
}


Floor::~Floor(void)
{
}

void Floor::Draw()
{
	// Draws an exciting chequered floor

	float x, y, z;
	/*
	glPushAttrib(GL_LIGHTING);              // Set the material properties of the waters surface
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMateriali(GL_FRONT, GL_SHININESS, matShininess);
	*/
	glEnable(GL_TEXTURE_2D);                // Enable texturing

	glBindTexture(GL_TEXTURE_2D, texId);    // Tell openGL which texture buffer to apply as texture

	glColor4f(1.0, 1.0, 1.0, 0.8);          // Set the base colour of the quad

	glPushMatrix();                                     // Move the quad to draw at the feet position
	glTranslatef(location[0], location[1], location[2]);
	glBegin(GL_QUADS);
	for(int j = -NUM_PATCHES; j < NUM_PATCHES; j ++)
	{
		for(int i = -NUM_PATCHES; i < NUM_PATCHES; i ++)
		{

			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0, 0.0, 1.0);

			glTexCoord2d(0, 1);   // Texture coordinate index into the top left sprite coord
			glVertex3f(PATCH_SIZE * (float)i, floorDepth, PATCH_SIZE * (float)j);        // Vertex coordinate of the top left of the quad

			glTexCoord2d(0, 0);   // Texture coordinate index into the bottom left sprite coord
			glVertex3f(PATCH_SIZE * (float)i, floorDepth, PATCH_SIZE * (float)j + PATCH_SIZE);           // Vertex coordinate of the bottom left of the quad

			glTexCoord2d(1, 0);   // Texture coordinate index into the bottom right sprite coord
			glVertex3f(PATCH_SIZE * (float)i + PATCH_SIZE, floorDepth, PATCH_SIZE * (float)j + PATCH_SIZE);           // Vertex coordinate of the bottom right of the quad

			glTexCoord2d(1, 1);   // Texture coordinate index into the top right sprite coord
			glVertex3f(PATCH_SIZE * (float)i + PATCH_SIZE, floorDepth, PATCH_SIZE * (float)j);        // Vertex coordinate of the top right of the quad
		}
	}

	glEnd();
	glPopMatrix();

	//glPopAttrib();  // remove the material properties from the material stack

	glBindTexture(GL_TEXTURE_2D, 0); // Bind to the blank buffer to stop ourselves accidentaly using the wrong texture in the next draw call

	glDisable(GL_TEXTURE_2D);

}
