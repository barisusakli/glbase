//////////////////////////////////////////////////////////////////////////
//glBase OpenGL3.2 Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif

#include <gl/GL.h>
#include <gl/GLU.h>
#include <functional>
#include <fstream>
#include <sstream>

#include "GLWindow.h"
#include "Exception.h"
#include "CoreFunctions.h"
#include "VertexBufferObject.h"
#include "IndexBufferObject.h"
#include "VertexArrayObject.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Matrix.h"
#include "ErrorCodes.h"
#include "VertexTypes.h"


glBase::VertexPositionColor data1[] = {
	glBase::VertexPositionColor(-0.4f,0.8f,0.0f),
	glBase::VertexPositionColor(-0.8f,-0.8f,0.0f),
	glBase::VertexPositionColor(0.0f,-0.8f,0.0f)
};

glBase::VertexPositionColor data2[]={
	glBase::VertexPositionColor(0.0f,0.8f,0.0f,1.0f,0.0f,0.0f),
	glBase::VertexPositionColor(0.4f,-0.8f,0.0f,0.0f,1.0f,0.0f),
	glBase::VertexPositionColor(0.8f,0.8f,0.0f,0.0f,0.0f,1.0f)
};

GLuint indices[] = {0,1,2};

std::unique_ptr<glBase::GLWindow> window;
std::unique_ptr<glBase::VertexArrayObject> vao1;
std::unique_ptr<glBase::VertexArrayObject> vao2;
bool quit = false;
bool fullscreen = false;

void render();

void onSize(int width, int height)
{
	window->activateContext();
	glViewport(0, 0, width, height);
}

void onSizing(int width, int height)
{
	window->activateContext();
	glViewport(0, 0, width, height);
	render();
}

void onKeyDown(glBase::Keys::Key key)
{
	if(key == glBase::Keys::Escape) 
		quit = true;
	
	if(key == glBase::Keys::F1)
	{
		fullscreen = !fullscreen;
		window->toggleFullscreen(fullscreen);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		glBase::DisplaySetting settings = {L"glBase Example", 800, 600, 32};
		window.reset(new glBase::GLWindow(settings, false));
		
		window->onSize.connect(&onSize);
		window->onSizing.connect(&onSizing);
		window->onKeyDown.connect(&onKeyDown);

		glBase::loadCoreFunctions();

		window->activateContext();
		glViewport(0, 0, settings.width, settings.height);
		
		glBase::VertexBufferObject vbo1((void*)&data1[0], 3*sizeof(glBase::VertexPositionColor));
		glBase::VertexBufferObject vbo2((void*)&data2[0], 3*sizeof(glBase::VertexPositionColor));
	
		glBase::IndexBufferObject ibo((void*)&indices[0],3*sizeof(GLuint));

		vao1.reset(new glBase::VertexArrayObject);
		vao1->bind();
		vbo1.bind();
		vao1->bindVertexAttribs(glBase::VertexPositionColor::vertexAttribs,glBase::VertexPositionColor::VERTEX_ATTRIB_COUNT);
		ibo.bind();
		vao1->unbind();

		vao2.reset(new glBase::VertexArrayObject);
		vao2->bind();
		vbo2.bind();
		vao2->bindVertexAttribs(glBase::VertexPositionColor::vertexAttribs,glBase::VertexPositionColor::VERTEX_ATTRIB_COUNT);
		vao2->unbind();
		
		glBase::VertexShader vertexShader(glBase::readFile("shaders\\minimal.vert"));
		glBase::FragmentShader fragmentShader(glBase::readFile("shaders\\minimal.frag"));

		glBase::ShaderProgram program(vertexShader, fragmentShader);

		program.link();
		program.use();
	
		unsigned int lastTicks = glBase::GLWindow::getTicks();
		while(window->isAlive() && !quit)
		{
			window->processMessages();

			unsigned int deltaTicks = glBase::GLWindow::getTicks() - lastTicks;
			lastTicks = deltaTicks + lastTicks;
			
			render();
		}
	}
	catch (const glBase::RuntimeException& e)
	{
		std::wstring final(e.m_Error.length()+e.m_At.length()+4,L'');
		std::string narrow = e.m_Error + std::string(" at ") + e.m_At;
		std::copy(narrow.begin(),narrow.end(),final.begin());

		glBase::GLWindow::messageBox(L"Unhandled exception!",final);
	}


	return 0;
}

void render()
{
	window->activateContext();

	glClearColor(0.3f,0.3f,0.6f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vao1->bind();
	glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)0);

	vao2->bind();
	glDrawArrays(GL_TRIANGLES,0,3);

	glFlush();

	window->swapBuffers();
}