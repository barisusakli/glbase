//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////


#ifndef INC_SHADER_H
#define INC_SHADER_H

#include <string>
#include <memory>
#include "CoreFunctions.h"

namespace glBase
{
	class Shader
	{
	public:
		Shader(GLenum shaderType, const std::string& code);
		~Shader();
		
		std::string getInfoLog();
		GLuint getID()const { return m_ID; }
	private:
		void construct(const std::string& code);

		GLenum m_Type;
		GLuint m_ID;
	};

	class VertexShader : public Shader
	{
	public:
		VertexShader(const std::string& code) : Shader(GL_VERTEX_SHADER,code) {}
	};

	class FragmentShader : public Shader
	{
	public:
		FragmentShader(const std::string& code) : Shader(GL_FRAGMENT_SHADER,code) {}
	};

}

#endif //INC_SHADER_H
