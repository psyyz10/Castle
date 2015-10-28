#include "StaticEngineWindows.h"
#include <string>
#include "InputReceiver.h"

StaticEngineWindows *StaticEngineWindows::current = 0;
HINSTANCE StaticEngineWindows::hInstance = 0;
HWND StaticEngineWindows::hwnd = 0;
HDC StaticEngineWindows::hdc = 0;
HGLRC StaticEngineWindows::hglrc = 0;
int StaticEngineWindows::windowWidth = 0;
int StaticEngineWindows::windowHeight = 0;
wchar_t* StaticEngineWindows::windowTitle = 0;
char *StaticEngineWindows::oldTitle = 0;
int StaticEngineWindows::windowID = 0;

StaticEngineWindows::StaticEngineWindows(int argc, char **argv, const char *title, const int& windowWidth, const int& windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	
	int length = strlen(title) + 1;
	this->windowTitle = new wchar_t[length];
	oldTitle = new char[length];
	strcpy(oldTitle, title);
	MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, title, -1, windowTitle, length);
}


StaticEngineWindows::~StaticEngineWindows(void)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	ReleaseDC(hwnd, hdc);
}


void StaticEngineWindows::Run(){

	current = this;

	printf("Running OpenGL Version: %s\n", glGetString(GL_VERSION));

	InitFunc();

	MSG msg;
	double millis;
	DWORD oldTime, newTime;
	oldTime = GetTickCount();
	while( 1 )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if( msg.message == WM_QUIT )
			{
				break;
			}

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			newTime = GetTickCount();
			millis = double(newTime - oldTime);
			millis /= 1000.0;
			oldTime = newTime;

			Update(millis);
			DrawFunc();
		}
	}
}

void StaticEngineWindows::InitFunc()
{
	// set background colour
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	// enable depth tests less than or equal
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// enable culling of backface polygons
	glEnable(GL_CULL_FACE);

	// enable transparancy blending
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enable 2D texturing
	glEnable(GL_TEXTURE_2D);

	// turn off 2 sided lighting
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// set the ambient light model
	GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	// enable directional light lighting
	// (x, y, z, 0.0) -> directional lighting
	// (x, y, z, 1.0) -> positional lighting
	glEnable(GL_LIGHTING);
	GLfloat ambience[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	// enable colored materials for lit objects
	glEnable(GL_COLOR_MATERIAL);

	// enable smooth shading from lighting
	glShadeModel(GL_SMOOTH);

	// enable automatic normalisation of normal vectors
	glEnable(GL_NORMALIZE);

	// enable automatic normalisation of normal vectors
	glEnable(GL_NORMALIZE);

	current->Init();
}

void StaticEngineWindows::DrawFunc() 
{
	current->DrawScene();

	if(!SwapBuffers(hdc))
	{
		DWORD error = GetLastError();
		FatalAppExit(NULL, TEXT("Error swapping buffers"));
	}
}


int StaticEngineWindows::CheckGLError()
{
	int e=0;
	GLenum error = glGetError();
	while ( GL_NO_ERROR != error )
	{
		e++;
		printf("GL Error %i: %s\n", e, gluErrorString(error));
		error = glGetError();
	}

	return e;
}



LRESULT CALLBACK StaticEngineWindows::WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	switch( message )
	{
	case WM_CREATE:
		Beep( 50, 10 );
		return 0;
		break;

	case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint( hwnd, &ps );
			EndPaint( hwnd, &ps );
		}
		return 0;
		break;

	case WM_KEYDOWN:
		switch( wparam )
		{
		case VK_ESCAPE:
			PostQuitMessage( 0 );
			break;
		default:
			HandleKeyPress(wparam, 1);
			break;
		}
		return 0;

	case WM_KEYUP:
		HandleKeyPress(wparam, 0);
		return 0;

	case WM_MOUSEMOVE:
		if(wparam & MK_LBUTTON || wparam & MK_RBUTTON || wparam & MK_MBUTTON)
		{
			current->MouseMotion(LOWORD(lparam), HIWORD(lparam));
		}
		else
		{
			current->PassiveMouseMotion(LOWORD(lparam), HIWORD(lparam));
		}
		return 0;

	case WM_LBUTTONDOWN:
		current->Mouse(0, 1, LOWORD(lparam), HIWORD(lparam));
		return 0;

	case WM_LBUTTONUP:
		current->Mouse(0, 0, LOWORD(lparam), HIWORD(lparam));
		return 0;

	case WM_MBUTTONDOWN:
		current->Mouse(1, 1, LOWORD(lparam), HIWORD(lparam));
		return 0;

	case WM_MBUTTONUP:
		current->Mouse(1, 0, LOWORD(lparam), HIWORD(lparam));
		return 0;

	case WM_RBUTTONDOWN:
		current->Mouse(2, 1, LOWORD(lparam), HIWORD(lparam));
		return 0;

	case WM_RBUTTONUP:
		current->Mouse(2, 0, LOWORD(lparam), HIWORD(lparam));
		return 0;

	case WM_SIZE:
		windowWidth = LOWORD(lparam);
		windowHeight = HIWORD(lparam);
		current->windowWidth = windowWidth;
		current->windowHeight = windowHeight;
		current->HandleResize(windowWidth, windowHeight);
		return 0;

	case WM_DESTROY:
		PostQuitMessage( 0 ) ;
		return 0;
		break;
	}

	return DefWindowProc( hwnd, message, wparam, lparam );
}


void StaticEngineWindows::RegisterWindow(HINSTANCE hinstance, int iCmdShow)
{
	hInstance = hinstance;

	WNDCLASS wc;
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );         
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );     
	wc.hInstance = hInstance;         
	wc.lpfnWndProc = StaticEngineWindows::WndProc;         
	wc.lpszClassName = TEXT("GLWindowClass");
	wc.lpszMenuName = 0; 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// Register that class with the Windows O/S..
	RegisterClass(&wc);

	RECT rect;
	SetRect( &rect, 50, 50, 50 + windowWidth, 50 + windowHeight ); // bottom
	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );
	
	hwnd = CreateWindow(TEXT("GLWindowClass"), windowTitle, WS_OVERLAPPEDWINDOW,
		rect.left, rect.top, windowWidth, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		FatalAppExit( NULL, TEXT("CreateWindow() failed!") );
	}
	
	// Get device context
	hdc = GetDC(hwnd);
	// Get pixel format descriptor

	PIXELFORMATDESCRIPTOR pfd = {0};

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	int chosenPixelFormat = ChoosePixelFormat(hdc, &pfd);

	if(chosenPixelFormat == 0)
	{
		FatalAppExit(NULL, TEXT("Unable to choose pixel format"));
	}

	if(SetPixelFormat(hdc, chosenPixelFormat, &pfd) == NULL)
	{
		FatalAppExit(NULL, TEXT("Unable to set pixelFormat"));
	}

	hglrc = wglCreateContext(hdc);

	wglMakeCurrent(hdc, hglrc);

	current = this;

	ShowWindow(hwnd, iCmdShow);
}


StaticEngineWindows* StaticEngineWindows::GetCurrentInstance()
{
	return StaticEngineWindows::current;
}

const char* StaticEngineWindows::GetWindowTitle()
{
	return StaticEngineWindows::oldTitle;
}

int StaticEngineWindows::GetWindowID()
{
	return StaticEngineWindows::windowID;
}

int StaticEngineWindows::GetWindowWidth()
{
	return StaticEngineWindows::windowWidth;
}

int StaticEngineWindows::GetWindowHeight()
{
	return StaticEngineWindows::windowHeight;
}

void StaticEngineWindows::HandleKeyPress(WPARAM wparam, int state)
{
	POINT p;
	if(!GetCursorPos(&p))
	{
		p.x = 0;
		p.y = 0;
	}
	
	int key = 0;

	switch(wparam)
	{
	case VK_F1:
	case VK_F2:
	case VK_F3:
	case VK_F4:
	case VK_F5:
	case VK_F6:
	case VK_F7:
	case VK_F8:
	case VK_F10:
	case VK_F11:
	case VK_F12:
		key = (int)wparam + 144;
		break;
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
		key = (int)wparam + 231;
		break;
	case VK_HOME:
		key = KEY_HOME;
		break;
	case VK_END:
		key = KEY_END;
		break;
	case VK_INSERT:
		key = KEY_INSERT;
		break;
	default:
		char c = (char)LOWORD(MapVirtualKeyA(wparam, MAPVK_VK_TO_CHAR));
		SHORT shift = (GetKeyState(VK_SHIFT) & 0x80) >> 7;
		SHORT caps = GetKeyState(VK_CAPITAL) & 0x1;

		if(!(caps != shift) && (int)c > 64 && (int)c < 90)
			c += 32;

		key = (int)c;
		break;
	}
	
	if(key == 0)
		return;

	current->HandleKey(key, state, p.x, p.y);
}