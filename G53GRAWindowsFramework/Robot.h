//
//  Robot.h
//  G53GRAMacFramework
//
//  Created by mac on 21/02/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#ifndef __G53GRAMacFramework__Robot__
#define __G53GRAMacFramework__Robot__

#include <iostream>
#include "DisplayableObject.h"

class Robot : public DisplayableObject
{
public:
    Robot(float x, float y, float z, int direction);
    ~Robot();
    void Draw();
	void DrawSun();
    void Update(const double& delytime);
    
private:
    void DrawHead();
    void DrawBody();
    void DrawArm();
    void DrawLeg();
    void DrawRobot(float x, float y, float z);
    float angle;
	int day; 
	float r, g, b;
    float position[3];
    bool forward;
    int direction;
    float speed,t;
    
};
#endif /* defined(__G53GRAMacFramework__Robot__) */
