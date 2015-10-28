
#pragma once

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "InputReceiver.h"

/*
The ViewController is used to handle viewing of the scene.  You can override this to provide your own functionality.  It contains
callbakcs for updating, input, and view-specific functions.
*/

class ViewController : public InputReceiver
{
public:
	ViewController();
	virtual ~ViewController();

	/* Update callback */
	virtual void Update( const double& deltatime ){}

	/* Input Handling Callbacks - defined in InputReceiver */
	virtual void HandleKey( int key, int state, int x, int y ){}
	virtual void HandleMouseClick(int button, int state, int x, int y){}
	virtual void HandleMouseMotion(int x, int y){}
	virtual void HandlePassiveMouseMotion(int x, int y) {}

	/* Projection Updates */
	// Called each time the window is resized.  Make sure the aspect ratio is correct in here.
	virtual void ScreenResized( const int& width, const int& height );
	// Called once per frame to set the projection
	virtual void SetProjection();
	// Called once per frame after SetProject, use it to set the camera position and orientation
	virtual void SetUpCamera();

	/* Static window size setter: Do not use */
	static void SetWindowSize( const int& width, const int& height );

protected:
	static int windowWidth, windowHeight;
};
