//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////

#ifndef INC_VERTEXTYPES_H
#define INC_VERTEXTYPES_H

#ifdef WIN32
#include <windows.h>
#endif

#include <gl/GL.h>

namespace glBase
{

	struct VERTEX_ATTRIBS 
	{
		GLuint index;
 		GLint size;
 		GLenum type;
 		GLboolean normalized;
 		GLsizei stride;
 		const GLvoid* pointer;
	};


	struct VertexPosition
    {
        VertexPosition()
			: x(0),y(0),z(0)            
        { }

        VertexPosition(float x,float y,float z)
          : x(x),y(y),z(z)            
        { }

        float x,y,z;

		static const int VERTEX_ATTRIB_COUNT=1;
		static const VERTEX_ATTRIBS vertexAttribs[VERTEX_ATTRIB_COUNT];
    };

	struct VertexPositionColor
	{
		VertexPositionColor()
        { }

        VertexPositionColor(float x,float y,float z,float r=1.0f,float g=1.0f,float b=1.0f)
          : x(x),y(y),z(z),r(r),g(g),b(b)            
        { }

        float x,y,z;
		float r,g,b;

		static const int VERTEX_ATTRIB_COUNT=2;
		static const VERTEX_ATTRIBS vertexAttribs[VERTEX_ATTRIB_COUNT];
	};

};

#endif