
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

/*
EngineObject defines an abstract class you can override to add an object to the scene.  
Any class you create which overrides EngineObject will need to implement the Update function, which
is called each frame with the time since the last update as the argument deltaTime
*/

class EngineObject
{
public:
	EngineObject(void) {}
	virtual ~EngineObject(void) {}

	// This function is called each frame.  Override to provide your own funcitonality
	virtual void Update( const double& deltaTime) = 0;
};

