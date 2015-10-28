//
//  Tree.h
//  G53GRAMacFramework
//
//  Created by mac on 14/03/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#ifndef __G53GRAMacFramework__Tree__
#define __G53GRAMacFramework__Tree__

#include <iostream>
#include "DisplayableObject.h"

class Tree:public DisplayableObject
{
public:
    Tree(float x, float y, float z);
    ~Tree();
    
    void Update(const double &deltatime);
    void Draw();
private:
    float position[3];

};

#endif /* defined(__G53GRAMacFramework__Tree__) */
