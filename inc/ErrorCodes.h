//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////

#ifndef INC_ERRORCODES_H
#define INC_ERRORCODES_H

#include <string>

#include <gl\GL.h>
#include <gl/GLU.h>
#include "gl\glcorearb.h"


namespace glBase
{

	const std::wstring getGLError() 
	{
		GLenum errorCode = glGetError();
		switch (errorCode)
		{
		case GL_NO_ERROR:
			return L"GL_NO_ERROR : No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
		case GL_INVALID_ENUM:
			return L"GL_INVALID_ENUM 0x0500: Given when an enumeration parameter is not a legal enumeration for that function. This is given only for local problems; if the spec allows the enumeration in certain circumstances, and other parameters or state dictate those circumstances, then GL_INVALID_OPERATION? is the result instead.";
		case GL_INVALID_VALUE:
			return L"GL_INVALID_VALUE? 0x0501: Given when a value parameter is not a legal value for that function. This is only given for local problems; if the spec allows the value in certain circumstances, and other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead.";
		case GL_INVALID_OPERATION:
			return L"GL_INVALID_OPERATION? 0x0502: Given when the set of state for a command is not legal for the parameters given to that command. It is also given for commands where combinations of parameters define what the legal parameters are.";
		case GL_OUT_OF_MEMORY:
			return L"GL_OUT_OF_MEMORY 0x0503: Given when performing an operation that can allocate memory, but the memory cannot be allocated. The results of OpenGL functions that return this error are undefined; it is allowable for partial operations to happen.";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return L"GL_INVALID_FRAMEBUFFER_OPERATION 0x0506: Given when doing anything that would attempt to read from or write/render to a framebuffer that is not complete, as defined here.";
		case GL_STACK_OVERFLOW:
			return L"GL_STACK_OVERFLOW? 0x0503: Given when a stack pushing operation cannot be done because it would overflow the limit of that stack's size.";
		case GL_STACK_UNDERFLOW:
			return L"GL_STACK_UNDERFLOW 0x0504: Given when a stack popping operation cannot be done because the stack is already at its lowest point.";
		default:
			return L"Unknow OpenGL error code.";
		}
	}

};



#endif