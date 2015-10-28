
#pragma once

#include "DisplayableObject.h"

/*
A simple example of how to create an object which will display something on the screen
*/

class Triangle : public DisplayableObject
{
public:
	Triangle();
	~Triangle();

	// Overridden functions from DisplayableObject
	void Draw();
	void Update( const double& time ){};

private:

};
