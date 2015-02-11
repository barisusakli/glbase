//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////

#if !defined(_WIN32) && !defined(__WIN32__)
#error "Wrong target!"
#endif

#include <functional>
#include <windows.h>
#include <gl/GL.h>
#include <functional>
#include "gl/glext.h"
#include "gl/wglext.h"

#include "GLWindow.h"
#include "Exception.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


extern int main(int argc, char* argv[]);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char* arg[]={{""}};
	return main(0,arg);
}

using namespace glBase;

static const std::wstring windowClassName = L"glBase Opengl3.2 Win32";
struct glBase::GLWindowPlatformData
{
	HWND  handle;
	HDC   device;
	HGLRC context;
};

static Keys::Key translateKey(unsigned int key, unsigned flags)
{
	switch (key)
    {
        case VK_MENU :       return (flags & (1 << 24)) ? Keys::RAlt     : Keys::LAlt;
        case VK_CONTROL :    return (flags & (1 << 24)) ? Keys::RControl : Keys::LControl;
        case VK_LWIN :       return Keys::LSystem;
        case VK_RWIN :       return Keys::RSystem;
        case VK_APPS :       return Keys::Menu;
        case VK_OEM_1 :      return Keys::SemiColon;
        case VK_OEM_2 :      return Keys::Slash;
        case VK_OEM_PLUS :   return Keys::Equal;
        case VK_OEM_MINUS :  return Keys::Dash;
        case VK_OEM_4 :      return Keys::LBracket;
        case VK_OEM_6 :      return Keys::RBracket;
        case VK_OEM_COMMA :  return Keys::Comma;
        case VK_OEM_PERIOD : return Keys::Period;
        case VK_OEM_7 :      return Keys::Quote;
        case VK_OEM_5 :      return Keys::BackSlash;
        case VK_OEM_3 :      return Keys::Tilde;
        case VK_ESCAPE :     return Keys::Escape;
        case VK_SPACE :      return Keys::Space;
        case VK_RETURN :     return Keys::Return;
        case VK_BACK :       return Keys::Back;
        case VK_TAB :        return Keys::Tab;
        case VK_PRIOR :      return Keys::PageUp;
        case VK_NEXT :       return Keys::PageDown;
        case VK_END :        return Keys::End;
        case VK_HOME :       return Keys::Home;
        case VK_INSERT :     return Keys::Insert;
        case VK_DELETE :     return Keys::Delete;
        case VK_ADD :        return Keys::Add;
        case VK_SUBTRACT :   return Keys::Subtract;
        case VK_MULTIPLY :   return Keys::Multiply;
        case VK_DIVIDE :     return Keys::Divide;
        case VK_PAUSE :      return Keys::Pause;
        case VK_F1 :         return Keys::F1;
        case VK_F2 :         return Keys::F2;
        case VK_F3 :         return Keys::F3;
        case VK_F4 :         return Keys::F4;
        case VK_F5 :         return Keys::F5;
        case VK_F6 :         return Keys::F6;
        case VK_F7 :         return Keys::F7;
        case VK_F8 :         return Keys::F8;
        case VK_F9 :         return Keys::F9;
        case VK_F10 :        return Keys::F10;
        case VK_F11 :        return Keys::F11;
        case VK_F12 :        return Keys::F12;
        case VK_F13 :        return Keys::F13;
        case VK_F14 :        return Keys::F14;
        case VK_F15 :        return Keys::F15;
        case VK_LEFT :       return Keys::Left;
        case VK_RIGHT :      return Keys::Right;
        case VK_UP :         return Keys::Up;
        case VK_DOWN :       return Keys::Down;
        case VK_NUMPAD0 :    return Keys::Numpad0;
        case VK_NUMPAD1 :    return Keys::Numpad1;
        case VK_NUMPAD2 :    return Keys::Numpad2;
        case VK_NUMPAD3 :    return Keys::Numpad3;
        case VK_NUMPAD4 :    return Keys::Numpad4;
        case VK_NUMPAD5 :    return Keys::Numpad5;
        case VK_NUMPAD6 :    return Keys::Numpad6;
        case VK_NUMPAD7 :    return Keys::Numpad7;
        case VK_NUMPAD8 :    return Keys::Numpad8;
        case VK_NUMPAD9 :    return Keys::Numpad9;
        case 'A' :           return Keys::A;
        case 'Z' :           return Keys::Z;
        case 'E' :           return Keys::E;
        case 'R' :           return Keys::R;
        case 'T' :           return Keys::T;
        case 'Y' :           return Keys::Y;
        case 'U' :           return Keys::U;
        case 'I' :           return Keys::I;
        case 'O' :           return Keys::O;
        case 'P' :           return Keys::P;
        case 'Q' :           return Keys::Q;
        case 'S' :           return Keys::S;
        case 'D' :           return Keys::D;
        case 'F' :           return Keys::F;
        case 'G' :           return Keys::G;
        case 'H' :           return Keys::H;
        case 'J' :           return Keys::J;
        case 'K' :           return Keys::K;
        case 'L' :           return Keys::L;
        case 'M' :           return Keys::M;
        case 'W' :           return Keys::W;
        case 'X' :           return Keys::X;
        case 'C' :           return Keys::C;
        case 'V' :           return Keys::V;
        case 'B' :           return Keys::B;
        case 'N' :           return Keys::N;
        case '0' :           return Keys::Num0;
        case '1' :           return Keys::Num1;
        case '2' :           return Keys::Num2;
        case '3' :           return Keys::Num3;
        case '4' :           return Keys::Num4;
        case '5' :           return Keys::Num5;
        case '6' :           return Keys::Num6;
        case '7' :           return Keys::Num7;
        case '8' :           return Keys::Num8;
        case '9' :           return Keys::Num9;
    }

    return Keys::Unknown;
}

unsigned int GLWindow::getTicks()
{
	return GetTickCount();
}

static void getGLVersion(int& major, int& minor)
{
	// for all versions
	char* ver = (char*)glGetString(GL_VERSION); // ver = "3.2.0"

	major = ver[0] - '0';
	if( major >= 3)
	{
		// for GL 3.x
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
	}
	else
	{
		minor = ver[2] - '0';
	}

	// GLSL version
	ver = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

static LRESULT CALLBACK eventHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	GLWindow* window;
	if (message == WM_CREATE)
	{
		long This = reinterpret_cast<long>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetWindowLongPtr(handle, GWLP_USERDATA, This);
	}
	else if((window = reinterpret_cast<GLWindow*>(GetWindowLongPtr(handle, GWLP_USERDATA))) != NULL)
	{
		switch (message)											
		{													
		case WM_SIZE:
			window->onSize(LOWORD(lParam),HIWORD(lParam));
			break;

		case WM_SIZING:
			{
				RECT* r = (RECT*)lParam;
				window->onSizing(r->right - r->left, r->bottom - r->top);
				return true;
			}

		case WM_CHAR:
			//window->onChar(wParam);
			break;

		case WM_KEYDOWN:
			if ((lParam & (1<<30)) == 0)
			{
				if(window->onKeyDown.num_slots())
					window->onKeyDown(translateKey(wParam,lParam));
			}
			break;

		case WM_KEYUP:
			if(window->onKeyUp.num_slots())
				window->onKeyUp(translateKey(wParam,lParam));
			break;

		case WM_ACTIVATEAPP:
			//window->onActivateApp(wParam == TRUE,(DWORD) lParam);
			break;

		case WM_CLOSE:
			window->onClose();
			break;

		case WM_DESTROY:
		default:
			break;
		}
	}
	return DefWindowProc(handle,message,wParam,lParam);
}
static void registerWindowClass()
{
	WNDCLASSW WindowClass;
	WindowClass.style         = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WindowClass.lpfnWndProc   = &eventHandler;
	WindowClass.cbClsExtra    = 0;
	WindowClass.cbWndExtra    = 0;
	WindowClass.hInstance     = GetModuleHandle(NULL);
	WindowClass.hIcon         = NULL;
	WindowClass.hCursor       = 0;
	WindowClass.hbrBackground = 0;
	WindowClass.lpszMenuName  = NULL;
	WindowClass.lpszClassName = windowClassName.c_str();

	RegisterClassW(&WindowClass);
}

GLWindow::GLWindow() : m_Data(new GLWindowPlatformData), m_Active(false), m_Fullscreen(false), m_Alive(true)
{
	registerWindowClass();
	m_Settings.bits  = 32;
	m_Settings.width  = 1;
	m_Settings.height = 1;
	
	m_Data->handle = CreateWindowW(windowClassName.c_str(), L"", WS_POPUP | WS_DISABLED, 0, 0, 1, 1, NULL, NULL, GetModuleHandle(NULL), (void*)this);
	ShowWindow(m_Data->handle, SW_HIDE);
	
	onClose.connect(std::tr1::bind(&GLWindow::closing,this));
}

GLWindow::GLWindow(const DisplaySetting& settings, bool fullscreen)
	: m_Data(new GLWindowPlatformData), m_Active(false), m_Fullscreen(fullscreen), m_Settings(settings), m_Alive(true)
{
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
	registerWindowClass();
	RECT windowRect;
	windowRect.left	  = 0;
	windowRect.right  = settings.width;
	windowRect.top	  = 0;
	windowRect.bottom = settings.height;

	//adjust windowRect so that the client area gives the dimensions we want		
	AdjustWindowRect(&windowRect, 0, false);

	//create window
	m_Data->handle = CreateWindowEx(NULL,
		windowClassName.c_str(),
		settings.title.c_str(),
		WS_SYSMENU | WS_SIZEBOX |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,//hParent,
		NULL,//hMenu
		hInstance,
		(void*)this);

	if(!m_Data->handle)
	{
		throw RuntimeException("Window Creation Failed",CURRENT_LOCATION);
	}

	// if everything goes well time to create opengl rendering context
	createGLContext(m_Settings.bits);

	// on the first run if we want fullscreen go fullscreen
	// don't do anything if m_Fullscreen is false on window creation
	if(m_Fullscreen)
		toggleFullscreen(true);
	ShowWindow(m_Data->handle,SW_SHOW);

	onClose.connect(std::tr1::bind(&GLWindow::closing,this));
}

void GLWindow::closing()
{
	m_Alive = false;
}

GLWindow::~GLWindow()
{
	if(m_Data->context!=NULL)
	{
		wglMakeCurrent(NULL,NULL); 
		wglDeleteContext(m_Data->context);
	}
	if(m_Data->device!=NULL)
	{
		ReleaseDC(m_Data->handle, m_Data->device);
	}
	if(m_Data->handle!=NULL)
	{
		DestroyWindow(m_Data->handle);
	}
	delete m_Data;

}

void GLWindow::processMessages()
{
	MSG Message;
	while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
}

void GLWindow::createGLContext(unsigned int bits)
{
	m_Data->device = GetDC(m_Data->handle);

	if(m_Data->device == NULL)
		throw RuntimeException("Can't get Device Context of Window", CURRENT_LOCATION);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1; 
	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   
	pfd.iPixelType = PFD_TYPE_RGBA; 
	pfd.cColorBits = bits;
	pfd.cDepthBits = 16; 
	pfd.iLayerType = PFD_MAIN_PLANE;

	//chose a pixel format
	int nPixelFormat = ChoosePixelFormat(m_Data->device, &pfd);

	if (nPixelFormat == 0)
		throw RuntimeException("Can't chose pixel format",CURRENT_LOCATION);

	BOOL result = SetPixelFormat(m_Data->device, nPixelFormat, &pfd);

	if (!result) 
		throw RuntimeException("Can't set pixel format",CURRENT_LOCATION);

	// create a temporary context to get 3.2
	m_Data->context = wglCreateContext(m_Data->device); 
	wglMakeCurrent(m_Data->device,m_Data->context);

	int major, minor;
	getGLVersion(major,minor);

	if( major < 3 || ( major == 3 && minor < 2 ) )
		throw RuntimeException("OpenGL 3.2 or higher is not supported!",CURRENT_LOCATION);

	
	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2, 
		WGL_CONTEXT_FLAGS_ARB,0, //WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,//| WGL_CONTEXT_DEBUG_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 
		0
	};

	
	HGLRC new_context=NULL;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
	if((wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB"))!=NULL)
		new_context = wglCreateContextAttribsARB(m_Data->device, 0, attribs);
	//delete temporary context

	wglMakeCurrent(NULL,NULL); 
	wglDeleteContext(m_Data->context);
	if(wglCreateContextAttribsARB == NULL || new_context == NULL)
		throw RuntimeException("OpenGL 3.x Rendering Context was not created!",CURRENT_LOCATION);

	m_Data->context = new_context;
	wglMakeCurrent(m_Data->device, m_Data->context);

}

void GLWindow::toggleFullscreen(bool fullscreen)
{
	m_Fullscreen = fullscreen;

	if(fullscreen)
	{
		//get the desktop resolution
		HWND desktop = GetDesktopWindow();
		RECT rect;
		GetClientRect(desktop,&rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		int bits = 32;


		DEVMODE dmSettings;	
		DWORD	maxHz =  0;

		memset(&dmSettings,0,sizeof(dmSettings));			

		dmSettings.dmSize=sizeof(dmSettings);

		int i=0;

		OSVERSIONINFO info;
		info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&info);

		while(EnumDisplaySettings(NULL,i,&dmSettings))
		{
			if(dmSettings.dmPelsWidth==width && dmSettings.dmPelsHeight==height && dmSettings.dmBitsPerPel==bits)
			{
				if(dmSettings.dmDisplayFrequency > maxHz)
				{
					maxHz = dmSettings.dmDisplayFrequency;
				}
			}
			i++;
		}	
		dmSettings.dmPelsWidth	= width;
		dmSettings.dmPelsHeight	= height;
		dmSettings.dmBitsPerPel = bits;
		dmSettings.dmFields     =  DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if(info.dwPlatformId == VER_PLATFORM_WIN32_NT)
		{
			dmSettings.dmFields |= DM_DISPLAYFREQUENCY;
			dmSettings.dmDisplayFrequency = maxHz;
		}

		int result = ChangeDisplaySettings(&dmSettings,CDS_FULLSCREEN);

		if(result != DISP_CHANGE_SUCCESSFUL)
		{
			throw RuntimeException("Display mode unavailable", CURRENT_LOCATION);
		}

		//change to fullscreen style
		SetWindowLongPtr(m_Data->handle,GWL_EXSTYLE,WS_EX_APPWINDOW);
		SetWindowLongPtr(m_Data->handle,GWL_STYLE,WS_POPUP);

		//SetWindowPos needs to be called after SetWindowLongPtr to make sure changes are applied
		SetWindowPos(m_Data->handle,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

		//maximize the window
		ShowWindow(m_Data->handle,SW_MAXIMIZE);
		SetFocus(m_Data->handle);
	}
	else
	{
		//need to call SW_RESTORE twice for some weird reason
		ShowWindow(m_Data->handle,SW_RESTORE);

		//go back to normal resolution
		ChangeDisplaySettings(NULL,0);

		//change back to overlapped window style
		SetWindowLongPtr(m_Data->handle,GWL_EXSTYLE,WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
		SetWindowLongPtr(m_Data->handle,GWL_STYLE,WS_OVERLAPPEDWINDOW);

		//SetWindowPos needs to be called after SetWindowLongPtr to make sure changes are applied
		SetWindowPos(m_Data->handle,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowWindow(m_Data->handle,SW_RESTORE);

		SetFocus(m_Data->handle);
	}
}	
void GLWindow::messageBox(const std::wstring& title, const std::wstring& message)
{
	MessageBoxW(NULL, message.c_str(), title.c_str(), MB_ICONEXCLAMATION|MB_OK);
}
void GLWindow::swapBuffers()
{
	SwapBuffers( m_Data->device );
}
void GLWindow::activateContext() const
{
	wglMakeCurrent(m_Data->device, m_Data->context);
}

std::vector<DisplaySetting> GLWindow::getAvailableDisplaySettings()
{
	std::vector<DisplaySetting> displaySettings;
	DEVMODE dmSettings;	
	DWORD	maxHz =  0;

	memset(&dmSettings,0,sizeof(dmSettings));			

	dmSettings.dmSize=sizeof(dmSettings);

	int i=0;

	OSVERSIONINFO info;
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&info);

	DisplaySetting ds;

	// go through all settings and add them to the vector one by one
	while(EnumDisplaySettings(NULL,i,&dmSettings))
	{
		ds.width = dmSettings.dmPelsWidth;
		ds.height = dmSettings.dmPelsHeight;
		ds.bits = dmSettings.dmBitsPerPel;

		//add the new setting to the vector
		displaySettings.push_back(ds);

		i++;
	}	
	return displaySettings;
}