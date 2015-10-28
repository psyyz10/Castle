
#pragma once

#include <vector>

class InputReceiver;
class ViewController;

/*
This class receives all input from the engine and forwards it to any input receivers it has registered with it.
You must not modify this class.
*/

class InputController
{

public:
	InputController(void);
	~InputController(void);

	void AddReceiver(InputReceiver *);
	void AddViewController(ViewController *view);

	void KeyPress( int key, int state, int x, int y );
	void MouseClick( int button, int state, int x, int y );
	void MouseMotion( int x, int y );
	void PassiveMouseMotion( int x, int y );

private:
	std::vector<InputReceiver*> receivers;
};

