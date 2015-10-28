#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\glu.h>

/*
Base class for the Windows engine, it handles the Win32 side of things, creating a window, setting up a rendering context,
input, updates, etc.  Do not modify this class.
*/

class StaticEngineWindows
{
public:
	StaticEngineWindows(int argc, char **argv, const char *title, const int& windowWidth, const int& windowHeight);
	virtual ~StaticEngineWindows(void);

	virtual void Run();

	static StaticEngineWindows* GetCurrentInstance();
	static const char* GetWindowTitle();
	static int GetWindowID();
	static int GetWindowWidth();
	static int GetWindowHeight();

	void RegisterWindow(HINSTANCE hinstance, int iCmdShow);                                      //maps to init();

protected:
	/* GLError checking */
	static int CheckGLError();

private:
	static StaticEngineWindows *current;

	/* Window information */
	static wchar_t* windowTitle;
	static char *oldTitle;
	static int windowID;

	/* Windows vars and callbacks */
	static int windowWidth;
	static int windowHeight;

	static HINSTANCE hInstance;
	static HWND hwnd;
	static HDC hdc;
	static HGLRC hglrc;

	static LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );


	/* Callbacks */
	static void InitFunc();                                         //maps to init();
	static void DrawFunc();                                         //maps to drawScene()

	/* Virtual callback overrides */
	virtual void Init() = 0;
	virtual void DrawScene() = 0;
	virtual void HandleResize( int w, int h ) = 0;
	virtual void HandleKey( int key, int state, int x, int y ) = 0;
	virtual void Mouse( int button, int state, int x, int y ) = 0;
	virtual void MouseMotion( int x, int y ) = 0;
	virtual void PassiveMouseMotion(int x, int y) = 0;
	virtual void Update( const double& ) = 0;

	static void HandleKeyPress(WPARAM wparam, int state);

};

