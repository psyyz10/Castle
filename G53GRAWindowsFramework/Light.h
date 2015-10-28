
#pragma once

#include "EngineObject.h"

class Camera;

class Light : public EngineObject
{
public:
    Light( Camera* c );
    ~Light();
    
    void Update( const double& deltatime );
    
private:
    
    Camera* cam;        // memeber variable to hold the camera pointer
    float position[4], ambient[4], diffuse[4], specular[4]; // member variables for the reflectance model parameters
    
};
