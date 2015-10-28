
#include "DisplayableObject.h"
#include "InputReceiver.h"

class Camera;

// A class to draw our skybox mjust be a displayable object so it can draw and is an input reciever so it can toggle between day and night on a button click

class Skybox : public DisplayableObject, public InputReceiver
{
    
public:
    Skybox( Camera * cam );
    ~Skybox();
    
    void Draw();    // function to inisialise the skybox position then draw it
    
private:
    
    void DrawBox();     // function to draw a skybox a given size with the correct winding
    
    Camera *c;          // member variable to store the camera object to query view direction
    GLuint texId[10];   // member variable to store handles to all our texture objects
    bool dayOrNight;    // member variable to toggle the day or night textures being used
    float size;         // member variable to descirbe how big our skybox should be
    
    
};
