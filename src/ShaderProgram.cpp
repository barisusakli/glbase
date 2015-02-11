//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////


#include "ShaderProgram.h"
#include "Exception.h"

namespace glBase
{

	ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& pixelShader) 
	{
		m_ID = glCreateProgram();

		if(!m_ID)
			throw RuntimeException("Error creating shader program",CURRENT_LOCATION);

		attachShader(vertexShader);
		attachShader(pixelShader);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}

	void ShaderProgram::attachShader(const Shader&  shader)
	{
		glAttachShader(m_ID, shader.getID());
	}

	void ShaderProgram::detachShader(const Shader&  shader)
	{
		glDetachShader(m_ID, shader.getID());
	}

	void ShaderProgram::link()
	{
		glBindAttribLocation(m_ID, 0, "in_Position");
		glBindAttribLocation(m_ID, 1, "in_Color");
		glBindAttribLocation(m_ID, 2, "in_Normal");
		glBindAttribLocation(m_ID, 3, "in_Tangent");
		glBindAttribLocation(m_ID, 4, "in_Bitangent");
		glBindAttribLocation(m_ID, 5, "in_TexCoord");
		glLinkProgram(m_ID); 

		int param;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &param);
		if(param != GL_TRUE) 
			throw RuntimeException("Error linking shader program", CURRENT_LOCATION);
	}

	void ShaderProgram::use()
	{
		glUseProgram(m_ID); 
	}

	std::string ShaderProgram::getInfoLog()const
	{
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;
		
		std::string infoString;
		glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 0)
		{
			infoLog = new char [infologLength];
			glGetShaderInfoLog(m_ID, infologLength, &charsWritten, infoLog);
			
			infoString = infoLog;
			delete [] infoLog;
		}
		return infoString;
	}
	
	GLint ShaderProgram::getUniformLocation(const std::string& name)
	{
		return glGetUniformLocation(m_ID, name.c_str());
	}
}