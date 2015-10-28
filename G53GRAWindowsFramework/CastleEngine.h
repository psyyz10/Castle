
#pragma once

#include "Engine.h"

/*
 The starting point for the coursework, this class overides the Engine class.  You can add to it as more parts of the coursework
 become possible by overriding functions from the Engine class.  Initially, you can set up your scene using the Init() function.
 */

class CastleEngine : public Engine
{
    
public:
	CastleEngine( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight );
	~CastleEngine();
    
private:
    
	void Init();
    
};
