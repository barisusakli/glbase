//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////


#ifndef INC_VERTEXARRAYOBJECT_H
#define INC_VERTEXARRAYOBJECT_H

#include "CoreFunctions.h"
#include "Vector3.h"
#include "VertexTypes.h"

namespace glBase
{
	class VertexArrayObject
	{
	public:
		VertexArrayObject()
		{
			glGenVertexArrays(1,&m_VAO);
		}
		
		void bind() const
		{
			glBindVertexArray(m_VAO);
		}

		void unbind() const
		{
			glBindVertexArray(0);
		}

		void bindVertexAttribs(const VERTEX_ATTRIBS attribs[],int count) const
		{
			for (int i = 0; i < count; i++)
			{
				const VERTEX_ATTRIBS& current = attribs[i];
				glEnableVertexAttribArray(current.index);
				glVertexAttribPointer(current.index, current.size, current.type, current.normalized, current.stride,current.pointer);
			}
		}

		~VertexArrayObject()
		{
			glDeleteVertexArrays(1,&m_VAO);
		}

		GLuint m_VAO;
	};
}



#endif //INC_VERTEXARRAYOBJECT_H

