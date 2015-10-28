
#include "Skybox.h"
#include "Engine.h"
#include "Camera.h"

Skybox::Skybox( Camera * cam ) : c(cam), dayOrNight(true), size(2.0)
{
    texId[0] = Engine::GetTexture("./front.bmp"); // First load each texture and remember their handles in the texId array
    texId[1] = Engine::GetTexture("./back.bmp");
    texId[2] = Engine::GetTexture("./left.bmp");
    texId[3] = Engine::GetTexture("./right.bmp");
    texId[4] = Engine::GetTexture("./top.bmp");
    
    texId[5] = Engine::GetTexture("./night_front.bmp");
    texId[6] = Engine::GetTexture("./night_back.bmp");
    texId[7] = Engine::GetTexture("./night_left.bmp");
    texId[8] = Engine::GetTexture("./night_right.bmp");
    texId[9] = Engine::GetTexture("./night_up.bmp");
}

Skybox::~Skybox()
{
    
}

void Skybox::Draw()
{
    // To make rendering as efficient as possible turn of as many features we dont need as possible
    glDisable(GL_DEPTH_TEST);       // Disable depth testing as we are going to draw it first it doesn't matter about depth!
    glDisable(GL_COLOR_MATERIAL);   // Disable colour material as we dont want the glColor calls to affect the texture colour
    glDisable(GL_LIGHTING);         // Disable lighting as we do not want lighting to effect our skybox
    glEnable(GL_TEXTURE_2D);        // Enable texturing so we can apply textures
    
    glPushMatrix();         // push the current Model_View matrix so any transforms to the skybox dont effect the rest of the scene
        glLoadIdentity();   // remove any transformations from the model_view matrix
                            // Set the model view matrix with gluLookAt so you can fix the camera to the center of the box and use the view direction to build the rotations
        gluLookAt(0,-size,0, c->GetViewDirection()[0], c->GetViewDirection()[1]-size, c->GetViewDirection()[2], 0,1,0);
        DrawBox();          // draw the skybox which will be effected by the rotations built by the gluLookAt call
    glPopMatrix();
    
    // re-enable and disable features so we leave the function with the same features active as we did when we entered
    glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
}

void Skybox::DrawBox()
{
    GLuint front, back, left, right, up;
    glColor4f(1.0, 1.0, 1.0, 1); 
    if(dayOrNight)                  // choose the texture handles based on the dayOrNight value
    {
        front = texId[1];           // day texture handles
        back = texId[0];
        left = texId[2];
        right = texId[3];
        up = texId[4];
    }
    else
    {
        front = texId[6];           // night texture handles
        back = texId[5];
        left = texId[7];
        right = texId[8];
        up = texId[9];
    }
    

    // draw the skybox with the correct polygon winding as the camera will be inside the box
    // back
    glBindTexture(GL_TEXTURE_2D, back);     // activate the use of the back texture
    glBegin(GL_QUADS);                      // start drawing a quad for the back face
        glTexCoord2d(0.0, 1.0);             // associate the top left texture coordinate with the
        glVertex3d( -size,  size - 0.5, -size);   // top left vertex coordinate
        glTexCoord2d(0.0, 0.0);             // associate the bottom left texture coordinate with the
        glVertex3d( -size, -size- 0.5, -size);   // bottom left vertex coordinate
        glTexCoord2d(1.0, 0.0);             // associate the bottom right texture coordinate with the
        glVertex3d(  size, -size- 0.5, -size);   // bottom right vertex coordinate
        glTexCoord2d(1.0, 1.0);             // associate the to right texture coordinate with the
        glVertex3d(  size,  size- 0.5, -size);   // top right vertex coordinate
    glEnd();                                // N.B. the polygon winding her is back to front in terms of the brick class you are used too using
    
    // front
    glBindTexture(GL_TEXTURE_2D, front);    // repeat for front face
    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 1.0);
        glVertex3d(  size,  size- 0.5,  size);
        glTexCoord2d(0.0, 0.0);
        glVertex3d(  size, -size- 0.5,  size);
        glTexCoord2d(1.0, 0.0);
        glVertex3d( -size, -size- 0.5,  size);
        glTexCoord2d(1.0, 1.0);
        glVertex3d( -size,  size- 0.5,  size);
    glEnd();

    // left
    glBindTexture(GL_TEXTURE_2D, left);     // repeat for left face
    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 1.0);
        glVertex3d( -size,  size- 0.5,  size);
        glTexCoord2d(0.0, 0.0);
        glVertex3d( -size, -size- 0.5,  size);
        glTexCoord2d(1.0, 0.0);
        glVertex3d( -size, -size- 0.5, -size);
        glTexCoord2d(1.0, 1.0);
        glVertex3d( -size,  size- 0.5, -size);
    glEnd();

    // right
    glBindTexture(GL_TEXTURE_2D, right);    // repeat for right face
    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 1.0);
        glVertex3d(  size,  size- 0.5, -size);
        glTexCoord2d(0.0, 0.0);
        glVertex3d(  size, -size- 0.5, -size);
        glTexCoord2d(1.0, 0.0);
        glVertex3d(  size, -size- 0.5,  size);
        glTexCoord2d(1.0, 1.0);
        glVertex3d(  size,  size- 0.5,  size);
    glEnd();

    // up
    glBindTexture(GL_TEXTURE_2D, up);       // repeat for top face
    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 1.0);
        glVertex3d( -size,  size- 0.5,  size);
        glTexCoord2d(0.0, 0.0);
        glVertex3d( -size,  size- 0.5, -size);
        glTexCoord2d(1.0, 0.0);
        glVertex3d(  size,  size- 0.5, -size);
        glTexCoord2d(1.0, 1.0);
        glVertex3d(  size,  size- 0.5,  size);
    glEnd();
    
}