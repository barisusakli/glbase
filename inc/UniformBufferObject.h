


#ifndef INC_UNIFORMBUFFER_H
#define INC_UNIFORMBUFFER_H

#include "Vector3.h"
#include "BufferObject.h"

namespace glBase
{
	class UniformBufferObject : public BufferObject
	{
	public:
		UniformBufferObject(const void* data, unsigned int size) : BufferObject(GL_ARRAY_BUFFER, size, GL_DYNAMIC_DRAW)
		{}
	};
}



#endif 