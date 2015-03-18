#include "GLManager.h"
using namespace Break::Renderer;
using namespace Break::Infrastructure;

GLManager::GLManager(){

}
GLManager::~GLManager(){

}

bool GLManager::init(ApplicationPtr app){
	//here comes the application pointer
	//you should take the IDisplay pointer and swap it with a similar Display<HWND> one with the same width, height, title

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	// Open a window and create its OpenGL context 
	// (In the accompanying source code, this variable is global) 
	window = glfwCreateWindow( app->_display->getWidth(), app->_display->getHeight(), app->_display->getTitle().c_str(), NULL, NULL); 
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version .\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW 
	glewExperimental=true; // Needed in core profile 
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	return true;
}

void GLManager::start()
{
	float clearColor[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	RenderFrame(clearColor);
}

void GLManager::clearBuffer()
{

}
void GLManager::swapBuffer()
{
	// Swap buffers
	glfwSwapBuffers(window);
}
void GLManager::setCursorPostion(glm::uvec2 val)
{

}

void GLManager::RenderFrame(float color[])
{
	glClearColor(color[0],color[1],color[2],color[3]);
	do{
		glClear(GL_COLOR_BUFFER_BIT);
		//Main loop start Here...<<----

		swapBuffer();
		glfwPollEvents();//<<-----that control input to be accessed on this window..
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

}