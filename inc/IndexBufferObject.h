//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////


#ifndef INC_INDEXBUFFER_H
#define INC_INDEXBUFFER_H

#include "Vector3.h"
#include "BufferObject.h"

namespace glBase
{
	class IndexBufferObject : public BufferObject
	{
	public:
		IndexBufferObject(const void* data, unsigned int size) : BufferObject(GL_ELEMENT_ARRAY_BUFFER, size, GL_STATIC_DRAW, data)
		{
			
		}

		void bind() const
		{
			BufferObject::bind();
		}
	};
}



#endif //INC_INDEXBUFFER_H
