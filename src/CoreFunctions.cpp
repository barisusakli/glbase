//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <fstream>
#include "CoreFunctions.h"

namespace glBase
{
	PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
	PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
	PFNGLUSEPROGRAMPROC glUseProgram = NULL;
	PFNGLATTACHSHADERPROC glAttachShader = NULL;
	PFNGLDETACHSHADERPROC glDetachShader = NULL;
	PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
	PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
	PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
	PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
	PFNGLUNIFORM1IPROC glUniform1i = NULL;
	PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
	PFNGLUNIFORM2IVPROC glUniform2iv = NULL;
	PFNGLUNIFORM3IVPROC glUniform3iv = NULL;
	PFNGLUNIFORM4IVPROC glUniform4iv = NULL;
	PFNGLUNIFORM1FPROC glUniform1f = NULL;
	PFNGLUNIFORM1FVPROC glUniform1fv = NULL;
	PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
	PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
	PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
	PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
	PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
	PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = NULL;
	PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = NULL;
	PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = NULL;
	PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = NULL;
	PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = NULL;
	PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
	PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;

	// Shader
	PFNGLCREATESHADERPROC glCreateShader = NULL;
	PFNGLDELETESHADERPROC glDeleteShader = NULL;
	PFNGLSHADERSOURCEPROC glShaderSource = NULL;
	PFNGLCOMPILESHADERPROC glCompileShader = NULL;
	PFNGLGETSHADERIVPROC glGetShaderiv = NULL;

	// VBO
	PFNGLGENBUFFERSPROC glGenBuffers = NULL;
	PFNGLBINDBUFFERPROC	glBindBuffer = NULL;
	PFNGLBUFFERDATAPROC	glBufferData = NULL;
	PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
	PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;

	PFNGLMAPBUFFERPROC glMapBuffer = NULL;
	PFNGLUNMAPBUFFERPROC glUnmapBuffer = NULL;
	PFNGLUNIFORMBUFFEREXTPROC glUniformBufferEXT = NULL;

	// VAO
	PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
	PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
	PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;


	void loadCoreFunctions()
	{
#ifdef WIN32
#define glGetProcAddress wglGetProcAddress
#endif
		// Program
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)glGetProcAddress("glCreateProgram");
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glGetProcAddress("glDeleteProgram");
		glUseProgram = (PFNGLUSEPROGRAMPROC)glGetProcAddress("glUseProgram");
		glAttachShader = (PFNGLATTACHSHADERPROC)glGetProcAddress("glAttachShader");
		glDetachShader = (PFNGLDETACHSHADERPROC)glGetProcAddress("glDetachShader");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)glGetProcAddress("glLinkProgram");
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glGetProcAddress("glGetProgramiv");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glGetProcAddress("glGetShaderInfoLog");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glGetProcAddress("glGetUniformLocation");
		glUniform1i = (PFNGLUNIFORM1IPROC)glGetProcAddress("glUniform1i");
		glUniform1iv = (PFNGLUNIFORM1IVPROC)glGetProcAddress("glUniform1iv");
		glUniform2iv = (PFNGLUNIFORM2IVPROC)glGetProcAddress("glUniform2iv");
		glUniform3iv = (PFNGLUNIFORM3IVPROC)glGetProcAddress("glUniform3iv");
		glUniform4iv = (PFNGLUNIFORM4IVPROC)glGetProcAddress("glUniform4iv");
		glUniform1f = (PFNGLUNIFORM1FPROC)glGetProcAddress("glUniform1f");
		glUniform1fv = (PFNGLUNIFORM1FVPROC)glGetProcAddress("glUniform1fv");
		glUniform2fv = (PFNGLUNIFORM2FVPROC)glGetProcAddress("glUniform2fv");
		glUniform3fv = (PFNGLUNIFORM3FVPROC)glGetProcAddress("glUniform3fv");
		glUniform4fv = (PFNGLUNIFORM4FVPROC)glGetProcAddress("glUniform4fv");
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glGetProcAddress("glUniformMatrix4fv");
		glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)glGetProcAddress("glGetAttribLocation");
		glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)glGetProcAddress("glVertexAttrib1f");
		glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)glGetProcAddress("glVertexAttrib1fv");
		glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)glGetProcAddress("glVertexAttrib2fv");
		glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)glGetProcAddress("glVertexAttrib3fv");
		glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)glGetProcAddress("glVertexAttrib4fv");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glGetProcAddress("glEnableVertexAttribArray");
		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glGetProcAddress("glBindAttribLocation");

		// Shader
		glCreateShader = (PFNGLCREATESHADERPROC)glGetProcAddress("glCreateShader");
		glDeleteShader = (PFNGLDELETESHADERPROC)glGetProcAddress("glDeleteShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)glGetProcAddress("glShaderSource");
		glCompileShader = (PFNGLCOMPILESHADERPROC)glGetProcAddress("glCompileShader");
		glGetShaderiv = (PFNGLGETSHADERIVPROC)glGetProcAddress("glGetShaderiv");

		// VBO
		glGenBuffers = (PFNGLGENBUFFERSPROC)glGetProcAddress("glGenBuffers");
		glBindBuffer = (PFNGLBINDBUFFERPROC)glGetProcAddress("glBindBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)glGetProcAddress("glBufferData");
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glGetProcAddress("glVertexAttribPointer");
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glGetProcAddress("glDeleteBuffers");
		glMapBuffer = (PFNGLMAPBUFFERPROC)glGetProcAddress("glMapBuffer");
		glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)glGetProcAddress("glUnmapBuffer");
		glUniformBufferEXT = (PFNGLUNIFORMBUFFEREXTPROC)glGetProcAddress("glUniformBufferEXT");

		// VAO
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glGetProcAddress("glBindVertexArray");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glGetProcAddress("glDeleteVertexArrays");
		
#undef glGetProcAddress
	}
	std::string readFile(const std::string& filename)
	{
		std::ifstream file(filename);
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

}

