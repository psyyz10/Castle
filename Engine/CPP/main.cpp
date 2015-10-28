
#include "CastleEngine.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char * argv[])
{
	CastleEngine *engine = NULL;

	// Create an instance of the castle engine
	engine = new CastleEngine(argc, argv, "G53GRA", 800, 700);

#ifdef _WIN32
	// WINDOWS stuff, don't worry about it
	HINSTANCE hinstance = GetModuleHandle(0);

	// Start the window
	engine->RegisterWindow(hinstance, SW_SHOWDEFAULT);
#endif
    
	// Start the engine running
	engine->Run();

	// clean up
	delete engine;

	return 0;
}


