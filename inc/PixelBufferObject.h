

#ifndef INC_PIXELBUFFER_H
#define INC_PIXELBUFFER_H


#include "BufferObject.h"

namespace glBase
{
	class PixelBufferObject : public BufferObject
	{
	public:
		PixelBufferObject(GLenum access, unsigned int size) : BufferObject(GL_PIXEL_UNPACK_BUFFER_ARB, size, GL_DYNAMIC_DRAW)
		{}
	};

	class WritablePixelBufferObject : public PixelBufferObject
	{
	public:
		WritablePixelBufferObject(unsigned int size):PixelBufferObject(GL_STREAM_DRAW,size)
		{
		}
	};
	
	class ReadablePixelBufferObject : public PixelBufferObject
	{
	public:
		ReadablePixelBufferObject(unsigned int size):PixelBufferObject(GL_STREAM_READ,size)
		{
		}
	};
}



#endif 
