#pragma once
#include "DisplayableObject.h"
#include "Camera.h"
#include <iostream>

class StreetLight:public DisplayableObject
{
public:
	StreetLight(Camera* c ,float x, float y, float z,int num,int direction);
	~StreetLight(void);
	void Update(const double &deltatime);
    void Draw();
	void DrawArm();             // function to draw and arm
    void DrawHead();            // function to draw the lamp head
	void drawHalfSphere(int scaley, int scalex, GLfloat r);
	float position[3],lightposition[4],ambient[4], diffuse[4], specular[4];
	int num, direction;
	Camera* cam;  
};

