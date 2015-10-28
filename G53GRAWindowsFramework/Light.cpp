
#include "Light.h"
#include "Camera.h"


Light::Light( Camera* c ) :  cam(c)
{
    // Positional Light: like a lamp in a room, objects are light based on the position and distance from the light source
    // Direction Light: like the sun, rays are parallel and every thing is light as though the light hit it at a given direction
    
    position[0] = 0.0;  // Set this as the light position if you want a positional light
    position[1] = 0.0;  // Or set it as the direction if you want a directional light
    position[2] = 1.0;
    position[3] = 0.0;  // Set this as 0.0 for directional light or 1.0 for a positional light
    
    ambient[0] = 0.3;  // Set the ambient colour of the light
    ambient[1] = 0.3;
    ambient[2] = 0.3;
    ambient[3] = 1.0;
    
    diffuse[0] = 1.0;   // Set the diffuse colour of the light
    diffuse[1] = 1.0;
    diffuse[2] = 1.0;
    diffuse[3] = 1.0;
    
    specular[0] = 1.0;  // Set the specular colour of the light
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;
}

Light::~Light()
{
    
}

void Light::Update( const double& deltatime )
{
    glEnable(GL_LIGHTING);      // turn lighting on
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);  // pass openGL the lighting model parameters for the Phong reflection model
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);   // Set the lights attentuation i.e. how quickly the light fades as we move away
    
    // FOR A LIGHT THAT MOVES WITH YOUR CAMERA
    // Light positions are stored in eye space the postion paramter is taken and multiplied by GL_MODEL_VIEW to
    // convert it from object to camera space, to get a light to move with your view, you must define it in camera space
    // therefore if we set the position while the model_view matrix == the identity matrix no transform from object to
    // view space will happen and our position in view space will be the paramter we passed. Therefore just call:
    glLightfv(GL_LIGHT0, GL_POSITION, position); // Uncomment this line for a light that moves with the camera
    // FOR A LIGHT THAT IS DEFINED AS A POSSION IN YOUR SCENE
    // the position array should hold its position in the scene then we must use the model_view transfrom matrix to calculate its position in
    // view space. Therefor, for a position define in world space, first set the object->view transfrom using the camera's SetUpCamera() function
    // then set the light position using glLightfv which will multiply the poistion ny the model_view matrix for you and store the lights
    // position in view coordinates.
    //cam->SetUpCamera();
    //glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    glEnable(GL_LIGHT0);
    
    
}