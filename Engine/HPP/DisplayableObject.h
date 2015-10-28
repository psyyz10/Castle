
#pragma once

#include "EngineObject.h"

/*
DisplayableObject defines an interface for an object which will draw something to the screen.  It derives EngineObject
and as such overrides the Update function.  Any classes you create which derive DisplayObject will need to implement both
the Draw and Update functions.
*/

class DisplayableObject : public EngineObject
{
public:
	DisplayableObject(void) : EngineObject() {}
	virtual ~DisplayableObject(void) {}

	// Called each frame after updates are done to draw it to the screen
	virtual void Draw() = 0;

	// Called each frame to update.
	virtual void Update( const double& deltaTime ){};
};

