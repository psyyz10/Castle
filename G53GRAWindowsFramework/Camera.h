//
//  Camera.h
//  G53GRAMacFramework
//
//  Created by mac on 28/02/2014.
//  Copyright (c) 2014 G53GRA. All rights reserved.
//

#ifndef __G53GRAMacFramework__Camera__
#define __G53GRAMacFramework__Camera__

#include <iostream>

#include "ViewController.h"
#include "EngineMath.h"

class Camera : public ViewController
{
public:
    Camera();
    ~Camera();
    
    void SetUpCamera();
    
    // Called every time a key is pressed or released
    void HandleKey(int key, int state, int x, int y);
    
    // Ignore this for now
    void SetProjection();
    
    void HandleMouseClick( int button, int state, int x, int y );
    
    void Update(const double& deltaTime);
    
    void HandleMouseMotion( int x, int y );
    
	float* GetViewDirection( );
   
    
    void Jump(const double &deltaTime);
    
private:
    float position[3];
    float rotation;
    bool wkey,skey,akey,dkey,fkey,gkey,jump;
    bool lMouse;
    float speed;
    float viewDirection[3];
    float upDirection[3];
    float rightDirection[3];
    float px, py;
    float jumpAnimation,jumpTranslation;
};

#endif /* defined(__G53GRAMacFramework__Camera__) */
