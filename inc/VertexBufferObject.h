//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////

#ifndef INC_VERTEXBUFFER_H
#define INC_VERTEXBUFFER_H

#include "Vector3.h"
#include "BufferObject.h"

namespace glBase
{
	class VertexBufferObject : public BufferObject
	{
	public:
		VertexBufferObject(const void* data, unsigned int size) : BufferObject(GL_ARRAY_BUFFER, size, GL_STATIC_DRAW, data)
		{
			
		}
		
		void bind() const
		{
			BufferObject::bind();
		}

		~VertexBufferObject()
		{

		}
	};
}



#endif //INC_VERTEXBUFFER_H
