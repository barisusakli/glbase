
#include "VertexTypes.h"


namespace glBase
{
	const VERTEX_ATTRIBS VertexPosition::vertexAttribs[]= {
		{0,3,GL_FLOAT,GL_FALSE,sizeof(VertexPosition),0}		
	};

	const VERTEX_ATTRIBS VertexPositionColor::vertexAttribs[]= {
		{0,3,GL_FLOAT,GL_FALSE,sizeof(VertexPositionColor),0},
		{1,3,GL_FLOAT,GL_FALSE,sizeof(VertexPositionColor),(GLvoid*)(3*sizeof(float))},
	};
		
}
