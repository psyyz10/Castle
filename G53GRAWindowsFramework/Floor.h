#pragma once
#include "displayableobject.h"
#include <string>

class Floor :
	public DisplayableObject
{
public:
	Floor(const int& gridX, const int& gridY, const float& xPos, const float& yPos, const float& zPos, const float& scale, const std::string& filePath);
	~Floor(void);
	void Draw();

private:
	GLuint texId;               // memeber variable used to store which buffer the texture is in on the GPU
    
	int xGridDims, yGridDims;   // dimensions of the water grid, how many squares in x and y direction
    //float *texCoords;           // list of texture coordinates for eah of the squares verticies
	double time;                // run time of the program
    bool frozen;
    
	GLfloat location[3];        // position of the grid in world space
	GLfloat scale;              // size of the grid in world space
	GLfloat texCoords[8];
	GLfloat matAmbient[4];      // matrial properties of the grid
	GLfloat matDiffuse[4];
	GLint matShininess;
	GLfloat matSpecular[4];
    float floorDepth;
};

