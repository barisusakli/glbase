//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////


#ifndef INC_BUFFER_H
#define INC_BUFFER_H

#include "CoreFunctions.h"

namespace glBase
{
	class BufferObject 
	{
	protected:
		BufferObject(GLenum type, unsigned int size, GLenum access, const void* data = 0) : m_Type(type), m_Size(size), m_Access(access)
		{
			glGenBuffers(1, &m_ID);
			glBindBuffer(type, m_ID);
			glBufferData(type, size, data, access);
			glBindBuffer(type, 0);
		}

		~BufferObject()
		{
			glDeleteBuffers(1, &m_ID);
		}

		void bind() const
		{
			glBindBuffer(m_Type, m_ID);
		}

		void unbind() const
		{
			glBindBuffer(m_Type, 0);
		}

	protected:
		friend class ShaderProgram;

		unsigned int m_ID;
		const GLenum m_Type;
		const unsigned int m_Size;
		const unsigned int m_Access;
	};
}

#endif 
