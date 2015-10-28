
#pragma once

#include "InputController.h"
#include "TextureManager.h"

#ifdef _WIN32
#include "StaticEngineWindows.h"
#define StaticEngine StaticEngineWindows
#else
#include "StaticEngineApple.h"
#define StaticEngine StaticEngineApple
#endif

#include <vector>

class ViewController;
class EngineObject;
class DisplayableObject;

/* The basic engine class, it deals with all the input callbacks, and windowing, and contains a list of objects to 
draw each frame.  You must not modify this, as it will not be used during marking.
*/

class Engine : public StaticEngine
{

public:
	Engine( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight );
	virtual ~Engine();

    // This function will load a texture at filename and upload it to a texture buffer
    // it returns the number / texture buffer reference it was uploaded to
	static int GetTexture(std::string fileName);
    
protected:

	// This function will be called before the window is opened
	virtual void Init() = 0;

	// This function will be called when the screen need to redraw i.e. use this function to draw the scene
	void DrawScene();
	// This function will be called when the window is resized
	void HandleResize( int w, int h );
	// This function will be called when a keyboard button is pressed
	void HandleKey( int key, int state, int x, int y );
	// This function will be called when a mouse button is pressed down/up
	void Mouse( int button, int state, int x, int y );
	// This function will be called when a mouse button is pressed then dragged
	void MouseMotion( int x, int y );
	// Called whenever the mouse moves
	void PassiveMouseMotion( int x, int y);
	// This function will be called when the screen isn't redrawing resizing or doing any processinf
	void Update( const double& deltatime );

    // This function will push a displayable object into the scene list so Draw and Update will be called on it
	void AddObjectToScene( EngineObject * object );

    // Thsi function will replace the default view controller with your own overrided version
	void AddCameraToScene( ViewController * camera );

private:

	InputController input;
	ViewController *view;
	static TextureManager textureManager;

	std::vector<EngineObject*> engObjects;
	std::vector<DisplayableObject*> dispObjects;
};

