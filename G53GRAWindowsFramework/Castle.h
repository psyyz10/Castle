//
//  Castle.h
//  G53GRAMacFramework
//
//  Created by mac on 29/03/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#ifndef __G53GRAMacFramework__Castle__
#define __G53GRAMacFramework__Castle__

#include <iostream>
#include "DisplayableObject.h"

class Castle:public DisplayableObject
{
public:
    Castle(float x, float y, float z,const std::string& filePath);
    ~Castle();
    void Update(const double &deltatime);
    void Draw();
    void DrawHead();
	void DrawWall();
	void DrawClouds();
	void DrawMainHead();
	void DrawFlage();
	void DrawCircle(float r, int num_segments) ;
	void Draw3DBrick(GLfloat size);
private:
    float position[3];
    int day;
	GLuint texId;               // memeber variable used to store which buffer the texture is in on the GPU
    GLuint texId2; 
};

#endif /* defined(__G53GRAMacFramework__Castle__) */
