//
//  Sun.h
//  G53GRAMacFramework
//
//  Created by mac on 31/03/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#ifndef __G53GRAMacFramework__Sun__
#define __G53GRAMacFramework__Sun__

#include <iostream>
#include "DisplayableObject.h"
#include "Camera.h"

class Sun:public DisplayableObject
{
public:
    Sun(float x, float y, float z);
    ~Sun();
    void Update(const double &deltatime);
    void Draw();
private:
    int day; 
	float position[4], ambient[4], diffuse[4], specular[4];
};

#endif /* defined(__G53GRAMacFramework__Sun__) */
