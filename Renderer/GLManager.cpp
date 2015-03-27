#include "GLManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Infrastructure/Display.h"
#include "../Infrastructure/Engine.h"
#include "GLMouse.h"
#include "GLKeyboard.h"
using namespace Break::Renderer;
using namespace Break::Infrastructure;

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glew32.lib")

GLManager::GLManager(){

}
GLManager::~GLManager(){

}

bool GLManager::init(ApplicationPtr app){
	//here comes the application pointer
	//you should take the IDisplay pointer and swap it with a similar Display<HWND> one with the same width, height, title
	GLFWwindow* window;
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL version 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //If requesting an OpenGL version below 3.2, GLFW_OPENGL_ANY_PROFILE

	// Open a window and create its OpenGL context

	window = glfwCreateWindow(app->_display->getWidth(), app->_display->getHeight(),app->_display->getTitle().c_str() , NULL, NULL);
	if( window == nullptr ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glewExperimental=true; // Needed in core profile 
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}
	Display<GLFWwindow*>* d = new Display<GLFWwindow*>(*app->_display);
	d->setHandle(window);
	app->_display = IDisplayPtr(d);
	return true;
}

void GLManager::start(){
	Display<GLFWwindow*>* d = dynamic_cast<Display<GLFWwindow*>*>(Engine::Instance->Application->_display.get());
	glfwSetKeyCallback(d->getHandle(),&Input::GLKeyboard::keyboardFunc);
	glfwSetMouseButtonCallback(d->getHandle(),&Input::GLMouse::mouseFunc);
	glfwSetCursorPosCallback(d->getHandle(),&Input::GLMouse::mouseMotion);
	while(!glfwWindowShouldClose(d->getHandle())){
		Engine::Instance->gameloop();
		glfwPollEvents();
	}
	d = NULL;
	return;
}

void GLManager::clearBuffer(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GLManager::swapBuffer(){
	Display<GLFWwindow*>* d = dynamic_cast<Display<GLFWwindow*>*>(Engine::Instance->Application->_display.get());
	glfwSwapBuffers(d->getHandle());
	d = NULL;
}
void GLManager::setCursorPostion(glm::uvec2 val){
	Display<GLFWwindow*>* d = dynamic_cast<Display<GLFWwindow*>*>(Engine::Instance->Application->_display.get());
	glfwSetCursorPos(d->getHandle(),(double)val.x,(double)val.y);
	d = NULL;
}