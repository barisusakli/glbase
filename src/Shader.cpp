

#include <vector>
#include <string>

#include "Shader.h"
#include "Exception.h"


namespace glBase
{
	Shader::Shader(GLenum shaderType, const std::string& code)
		: m_Type(shaderType), m_ID(0)
	{
		m_ID = glCreateShader(shaderType);
		construct(code);
	}

	void Shader::construct(const std::string& code)
	{
		const char *ccode = code.c_str();
		glShaderSource(m_ID, 1, (const char**) &ccode, NULL);
		glCompileShader(m_ID);
		
		int param;
		glGetShaderiv(m_ID, GL_COMPILE_STATUS, &param);
		if(param == GL_FALSE)
		{
			throw RuntimeException(std::string("Error compiling shader!\n ") + getInfoLog(), CURRENT_LOCATION);
		}
	}

	Shader::~Shader()
	{
		glDeleteShader(m_ID);
	}
	
	std::string Shader::getInfoLog()
	{
		int infologLength = 0;
		std::string logString;

		glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 0)
		{
			char *infoLog;
			infoLog = new char [infologLength];
			glGetShaderInfoLog(m_ID, infologLength, 0, infoLog);
			logString = infoLog;
			delete [] infoLog;
		}

		return logString;	
	}
}
