
#pragma once

/*
This interface allows your object to capture keyboard and mouse input.  Contains four functions, one for keyboard input,
one for mouse clicks, and two for mouse motion, and active and a passive function.  The active function is only called if a mouse
button is down, whereas the passive function is called whenever the mouse moves.  If you 
*/

// NORMAL KEYS MAP TO 0-255 for their ASCII unisgined char value
// Here are some defines for exra key types not in ASCII range
#define KEY_F1			256
#define KEY_F2			257
#define KEY_F3			258
#define KEY_F4			259
#define KEY_F5			260
#define KEY_F6			261
#define KEY_F7			262
#define KEY_F8			263
#define KEY_F9			264
#define KEY_F10			265
#define KEY_F11			266
#define KEY_F12			267

#define KEY_LEFT		268
#define KEY_UP			269
#define KEY_RIGHT		270
#define KEY_DOWN		271
#define KEY_PAGE_UP		272
#define KEY_PAGE_DOWN   273
#define KEY_HOME		274
#define KEY_END			275
#define KEY_INSERT		276

class InputReceiver 
{
public:
	InputReceiver(void) {}
	virtual ~InputReceiver(void) {}

	// Called when keyboard input is received - x and y are the mouse coordinates at the time when the key was pressed
	virtual void HandleKey(int key, int state, int x, int y ){}
	// Called when a mouse button is pressed, or released.  x and y are the mouse position
	virtual void HandleMouseClick( int button, int state, int x, int y ){}
	// Called when the mouse moves if a button is pressed, x and y are the mouse position
	virtual void HandleMouseMotion( int x, int y ){}
	// Called every time the mouse moves, x and y are the mouse position.
	virtual void HandlePassiveMouseMotion( int x, int y ){}
};

