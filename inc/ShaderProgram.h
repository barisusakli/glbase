


#ifndef INC_SHADERPROGRAM_H
#define INC_SHADERPROGRAM_H

#include <memory>
#include "CoreFunctions.h"
#include "UniformBufferObject.h"
#include "VertexBufferObject.h"
#include "PixelBufferObject.h"
#include "Shader.h"

namespace glBase
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
		
		~ShaderProgram();

		void link();
		void use();	

		std::string getInfoLog()const; 

		void bindUniformBufferObject(const std::string& name, const UniformBufferObject& object)
		{
			GLint location = getUniformLocation(name);
			object.bind();
			glUniformBufferEXT(m_ID, location, object.m_ID);
			object.unbind();
		}

	private:
		void attachShader(const Shader& shader);
		void detachShader(const Shader& shader);
		GLint getUniformLocation(const std::string& name);
		GLint getAttribLocation(const std::string& name);
		unsigned int m_ID;		

	};
}


#endif //INC_SHADERPROGRAM_H