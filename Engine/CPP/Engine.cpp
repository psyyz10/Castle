
#include "Engine.h"

#include "InputReceiver.h"
#include "DisplayableObject.h"
#include "EngineObject.h"
#include "ViewController.h"

#ifdef _WIN32
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#endif

TextureManager Engine::textureManager = TextureManager();

Engine::Engine( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight ) : StaticEngine(argc, argv, title, windowWidth, windowHeight), view(new ViewController())
{
	input.AddViewController(view);
}

Engine::~Engine()
{
	for(EngineObject* obj : engObjects)
	{
		if(obj != NULL)
			delete obj;
		obj = NULL;
	}
	if(view!=NULL)
		delete view;
	view = NULL;
}

void Engine::Init()
{
}

void Engine::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	view->SetProjection();
	view->SetUpCamera();
	for( DisplayableObject* obj : dispObjects)
		obj->Draw();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CheckGLError();
}

void Engine::HandleResize(int w, int h)
{
	ViewController::SetWindowSize( w, h );
	view->ScreenResized(w, h);
}

void Engine::HandleKey( int key, int state, int x, int y )
{
    input.KeyPress(key, state, x, y);
}

void Engine::Mouse(int button, int state, int x, int y)
{
	input.MouseClick(button, state, x, y);
}

void Engine::MouseMotion(int x, int y)
{
	input.MouseMotion(x, y);   
}

void Engine::PassiveMouseMotion( int x, int y)
{
	input.PassiveMouseMotion(x, y);
}

void Engine::Update( const double& deltatime )
{
	view->Update(deltatime);
	for( EngineObject* obj : engObjects )
		obj->Update(deltatime);
}

void Engine::AddObjectToScene( EngineObject * object )
{
	engObjects.push_back(object);

	DisplayableObject *dispObj = dynamic_cast<DisplayableObject*>(object);

	if(dispObj != NULL)
	{
		dispObjects.push_back(dispObj);
	}

	InputReceiver *receiver = dynamic_cast<InputReceiver*>(object);

	if(receiver != NULL)
	{
		input.AddReceiver(receiver);
	}
}

void Engine::AddCameraToScene(ViewController* camera)
{
	input.AddViewController(camera);
	if(view!=NULL)
		delete view;
	view = camera;
}

int Engine::GetTexture(std::string fileName)
{
	return textureManager.GetTexture(fileName);
}