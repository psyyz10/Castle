
#include "InputController.h"
#include "InputReceiver.h"
#include "ViewController.h"

using namespace std;

InputController::InputController(void)
{
}


InputController::~InputController(void)
{
	vector<InputReceiver*>().swap(receivers);
}


void InputController::AddReceiver(InputReceiver *receiver)
{
	receivers.push_back(receiver);
}

void InputController::AddViewController( ViewController* view )
{
	ViewController *oldV;

	if(receivers.empty()){
		receivers.push_back(dynamic_cast<InputReceiver*>(view));
	}
	else
	{
		oldV = dynamic_cast<ViewController*>(receivers[0]);
		if( oldV != NULL )
		{
			receivers[0] = dynamic_cast<InputReceiver*>(view);
		}
		else
		{
			receivers.insert(receivers.begin(), dynamic_cast<InputReceiver*>(view));
		}
	}
}

void InputController::KeyPress(int key, int state, int x, int y)
{
	for(InputReceiver *ir : receivers)
	{
		if(ir != NULL)
			ir->HandleKey(key, state, x, y);
	}
}


void InputController::MouseClick(int button, int state, int x, int y)
{
	for(InputReceiver *ir : receivers)
	{
		if(ir != NULL)
			ir->HandleMouseClick(button, state, x, y);
	}
}


void InputController::MouseMotion(int x, int y)
{
	for(InputReceiver *ir : receivers)
	{
		if(ir != NULL)
			ir->HandleMouseMotion(x, y);
	}
}

void InputController::PassiveMouseMotion(int x, int y)
{
	for(InputReceiver *ir : receivers)
	{
		if(ir != NULL)
			ir->HandlePassiveMouseMotion(x, y);
	}
}