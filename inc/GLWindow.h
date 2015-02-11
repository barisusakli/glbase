///////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////

#ifndef INC_GLWINDOW_H
#define INC_GLWINDOW_H

#include <string>
#include <vector>
#include <boost/signals2.hpp>

namespace glBase
{
	// represents display settings
	struct DisplaySetting
	{
		std::wstring title;
		int width;
		int height;
		int bits;
	};

	struct GLWindowPlatformData;

	namespace Keys
	{
		enum Key
		{
			Unknown,
			A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
			F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,
			Num0,Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8,Num9,
			Numpad0,Numpad1,Numpad2,Numpad3,Numpad4,Numpad5,Numpad6,Numpad7,Numpad8,Numpad9,
			Left,Right,Up,Down,
			Tab,RAlt,LAlt,RControl,LControl,LSystem,RSystem,Menu,SemiColon,Slash,Equal,Dash,LBracket,RBracket,
			Comma,Period,Quote,BackSlash,Tilde,Escape,Space,Return,Back,PageUp,PageDown,End,Home,
			Insert,Delete,Add,Subtract,Multiply,Divide,Pause,
		};
	}

	// GLWindow creates a GL window and processes input
	class GLWindow
	{
	public:
		GLWindow(); 							
		GLWindow(const DisplaySetting& settings, bool fullscreen=false);
		~GLWindow();

		void processMessages(); 		
		void toggleFullscreen(bool fullscreen); 
		void swapBuffers();
		std::vector<DisplaySetting> getAvailableDisplaySettings();

		void activateContext() const;;
		inline bool isAlive() const
		{ return m_Alive; }

		boost::signals2::signal<void(int,int)> onSize;
		boost::signals2::signal<void()> onClose;
		boost::signals2::signal<void(int,int)> onSizing;

		boost::signals2::signal<void(Keys::Key)> onKeyUp;
		boost::signals2::signal<void(Keys::Key)> onKeyDown;

		
		
		static void messageBox(const std::wstring& title, const std::wstring& message);
		static unsigned int getTicks();
	private:
		GLWindowPlatformData *m_Data;
		DisplaySetting m_Settings;
		
		bool m_Active;
		bool m_Fullscreen;
		bool m_Alive;

		void closing();
		void createGLContext(unsigned int bits);
	};
}


#endif INC_GLWINDOW_H