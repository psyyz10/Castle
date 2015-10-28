

#include "ViewController.h"
#include "CastleEngine.h"

int ViewController::windowWidth = 1;
int ViewController::windowHeight = 1;

ViewController::ViewController() : InputReceiver()
{
	ViewController::windowWidth = CastleEngine::GetWindowWidth();
	ViewController::windowHeight = CastleEngine::GetWindowHeight();
}

ViewController::~ViewController()
{

}

void ViewController::ScreenResized( const int& width, const int& height )
{    
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

void ViewController::SetProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-windowWidth/2, windowWidth/2, -windowHeight/2, windowHeight/2, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void ViewController::SetUpCamera()
{
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}

void ViewController::SetWindowSize( const int& width, const int& height )
{
	ViewController::windowWidth = width;
	ViewController::windowHeight = height;
}
