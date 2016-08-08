
#include "stdafx.h"
#include <stdio.h>
#include <string>

#include "SDL.h"

#include "Main.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GL.h>



using namespace std;

bool drawGlScene()
{
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}


//
//BOOL CreateGlWindow(char* title, int width, int height, int bits, bool fullscreenflag)
//{
//	if (fullscreenflag)
//	{
//		width = GetSystemMetrics(SM_CXSCREEN);
//		height = GetSystemMetrics(SM_CYSCREEN);
//	}
//	GLuint PixelFormat;
//	WNDCLASS wc;
//	DWORD dwExStyle;
//	DWORD dwStyle;
//	RECT WindowRect;
//	WindowRect.left = (long)0;
//	WindowRect.right = (long)width;
//	WindowRect.top = (long)0;
//	WindowRect.bottom = (long)height;
//	fullscreen = fullscreenflag;
//
//	hInstance = GetModuleHandle(NULL);
//	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//	wc.lpfnWndProc = (WNDPROC)WndProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = NULL;
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = "OpenGL";
//
//	if (!RegisterClass(&wc))
//	{
//		MessageBoxA(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONINFORMATION);
//		return FALSE;
//	}
//	if (fullscreen)
//	{
//		dwExStyle = WS_EX_APPWINDOW;
//		dwStyle = WS_POPUP;
//		ShowCursor(FALSE);
//	}
//	else
//	{
//		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
//		dwStyle = WS_OVERLAPPEDWINDOW;
//	}
//	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
//	if (!(hwnd = CreateWindowEx(dwExStyle, "OpenGL", title, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, NULL, NULL, hInstance, NULL)))
//	{
//		KillGLWindow();
//		MessageBoxA(NULL, "Window Creation Error", "ERROR", MB_OK | MB_ICONINFORMATION);
//		return FALSE;
//	}
//	static PIXELFORMATDESCRIPTOR pfd =
//	{
//		sizeof(PIXELFORMATDESCRIPTOR),
//		1,
//		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA,
//		bits,
//		0, 0, 0, 0, 0, 0,
//		0,
//		0,
//		0,
//		0, 0, 0, 0,
//		16,
//		0,
//		0,
//		PFD_MAIN_PLANE,
//		0,
//		0,0,0
//	};
//	if (!(hdc = GetDC(hwnd)))
//	{
//		KillGLWindow();
//		MessageBoxA(NULL, "Can't create a gl device context.", "ERROR", MB_OK | MB_ICONERROR);
//		return FALSE;
//	}
//	if (!(PixelFormat = ChoosePixelFormat(hdc, &pfd)))
//	{
//		KillGLWindow();
//		MessageBoxA(NULL, "Can't find a suitable pixel format.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;
//	}
//	if (!(SetPixelFormat(hdc, PixelFormat, &pfd)))
//	{
//		KillGLWindow();
//		MessageBoxA(NULL, "Can't set the pixel format", "ERROR", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;
//	}
//	if (!(hrc = wglCreateContext(hdc)))
//	{
//		KillGLWindow();
//		MessageBoxA(NULL, "Cant create a gl rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;
//	}
//	if (!wglMakeCurrent(hdc, hrc))
//	{
//		KillGLWindow();
//		MessageBoxA(NULL, "Cant activate the gl rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;
//	}
//	ShowWindow(hwnd, SW_SHOW);
//	SetForegroundWindow(hwnd);
//	SetFocus(hwnd);
//	ReSizeGLScene(width, height);
//	if (!InitGL())
//	{
//		KillGLWindow();
//		MessageBoxA(NULL, "Initialization failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;
//	}
//	return TRUE;
//}
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (uMsg)
//	{
//	case WM_ACTIVATE:
//	{
//		if (!HIWORD(wParam))
//		{
//			active = true;
//		}
//		else
//		{
//			active = false;
//		}
//		return 0;
//	}
//	case WM_SYSCOMMAND:
//	{
//		switch (wParam)
//		{
//		case SC_SCREENSAVE:
//		case SC_MONITORPOWER:
//			return 0;
//		}
//		break;
//	}
//	case WM_CLOSE:
//	{
//		PostQuitMessage(0);
//		return 0;
//	}
//	case WM_KEYDOWN:
//	{
//		keys[wParam] = TRUE;
//		return 0;
//	}
//	case WM_KEYUP:
//	{
//		keys[wParam] = FALSE;
//		return 0;
//	}
//	case WM_SIZE:
//	{
//		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
//		return 0;
//	}
//	}
//	return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}
//
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstancem, LPSTR lpCmdLine, int nCmdShow)
//{
//	MSG msg;
//	BOOL done = false;
//	if (MessageBoxA(NULL, "Would you like to run in fullscreen mode?", "Start Fullscreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
//	{
//		fullscreen = FALSE;
//	}
//	if (!CreateGlWindow("Chris' window", 640, 480, 16, fullscreen))
//	{
//		return 0;
//	}
//	while (!done)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			if (msg.message == WM_QUIT)
//			{
//				done = true;
//			}
//			else
//			{
//				TranslateMessage(&msg);
//				DispatchMessage(&msg);
//			}
//		}
//		else
//		{
//			if (active)
//			{
//				if (keys[VK_ESCAPE])
//				{
//					done = true;
//				}
//				else
//				{
//					DrawGLScene();
//					SwapBuffers(hdc);
//					if (keys['L'] && !lp)
//					{
//						lp = TRUE;
//						light = !light;
//						if (!light)
//						{
//							glDisable(GL_LIGHTING);
//							glDisable(GL_COLOR_MATERIAL);
//						}
//						else
//						{
//							glEnable(GL_LIGHTING);
//							glEnable(GL_COLOR_MATERIAL);
//						}
//					}
//					if (!keys['L'])
//					{
//						lp = FALSE;
//
//					}
//					if (keys['F'] && !fp)
//					{
//						fp = TRUE;
//						filter += 1;
//						if (filter > 2)
//						{
//							filter = 0;
//						}
//					}
//					if (!keys['F'])
//					{
//						fp = FALSE;
//					}
//					if (keys[VK_UP])
//					{
//						xpos -= (float)sin(heading *piover180) * 0.05f;
//						zpos -= (float)cos(heading *piover180) * 0.05f;
//						if (walkbiasangle >= 359.0f)
//						{
//							walkbiasangle = 0.0f;
//						}
//						else
//						{
//							walkbiasangle += 10;
//						}
//						walkbiasangle = (float)sin(walkbiasangle*(piover180) / 20.0f);
//					}
//					if (keys[VK_DOWN])
//					{
//						xpos += (float)sin(heading*piover180) * 0.005f;          // Move On The X-Plane Based On Player Direction
//						zpos += (float)cos(heading*piover180) * 0.005f;          // Move On The Z-Plane Based On Player Direction
//						if (walkbiasangle <= 1.0f)                   // Is walkbiasangle<=1?
//						{
//							walkbiasangle = 359.0f;                 // Make walkbiasangle Equal 359
//						}
//						else                                // Otherwise
//						{
//							walkbiasangle -= 10;                 // If walkbiasangle > 1 Decrease It By 10
//						}
//						walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
//					}
//					if (keys[VK_LEFT])
//					{
//						yRot += 0.5f;
//						heading = yRot;
//					}
//					if (keys[VK_RIGHT])
//					{
//						yRot -= 0.5f;
//						heading = yRot;
//
//					}
//					if (keys['B'] && !bp)
//					{
//						bp = TRUE;
//						blend = !blend;
//						if (blend)
//						{
//							glEnable(GL_BLEND);
//							glDisable(GL_DEPTH_TEST);
//						}
//						else
//						{
//							glDisable(GL_BLEND);
//							glEnable(GL_DEPTH_TEST);
//						}
//					}
//					if (keys['T'] && !tp)
//					{
//						tp = TRUE;
//						twinkle = !twinkle;
//					}
//					if (!keys['T'])
//					{
//						tp = FALSE;
//					}
//					if (keys[VK_PRIOR])
//					{
//						lookupdown -= 0.5f;
//					}
//
//					if (keys[VK_NEXT])
//					{
//						lookupdown += 0.5f;
//					}
//					if (keys['W'])
//					{
//						ypos -= 0.005f;
//					}
//					if (keys['S'])
//					{
//						ypos += 0.005f;
//					}
//					if (keys['A'])
//					{
//						scaleValue += 0.001f;
//					}
//					if (keys['D'])
//					{
//						scaleValue -= 0.001f;
//					}
//					if (keys[VK_SPACE])
//					{
//						waterN[waterSize / 2 - 1][waterSize / 2 - 1] = 1;
//					}
//				}
//				if (!keys['B'])
//				{
//					bp = FALSE;
//				}
//			}
//		}
//		if (keys[VK_F1])
//		{
//			keys[VK_F1] = FALSE;
//			KillGLWindow();
//			fullscreen = !fullscreen;
//			if (!CreateGlWindow("Chris' window", 640, 480, 16, fullscreen))
//			{
//				return 0;
//			}
//		}
//	}
//	KillGLWindow();
//	return(msg.wParam);
//}

int main(int argc, char* argv[])
{
	SDL_Window *mainWindow;
	SDL_GLContext mainContext;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 0;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	string windowName = "";
	#ifdef _WIN32
		windowName = "Windows GL";
	#else
		windowName = "Unix GL";
	#endif
	mainWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!mainWindow)
	{
		return 0;
	}
	
	mainContext = SDL_GL_CreateContext(mainWindow);
	SDL_GL_SetSwapInterval(1);
	bool done = false;
	while (!done)
	{
		drawGlScene();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				done = true;
			}
		}
		SDL_GL_SwapWindow(mainWindow);
	}
	return 0;

}