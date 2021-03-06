#include "GLManager.h"
#include <GLFW/glfw3.h>
#include "Display.h"
#include "Engine.h"
#include "GLMouse.h"
#include "GLKeyboard.h"
#include "GLHandle.h"
#include <memory>
#include "IGPUHandle.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GPUResource.h"
#include "GlobalDefinitions.h"
#include "GPUException.h"
#include "Shader.h"
#include "GLShaderHandle.h"
#include "UniformBuffer.h"
#include "Texture2D.h"
#include <cstring>
using namespace std;
using namespace Break::Renderer;
using namespace Break::Infrastructure;
using namespace Break;
using namespace Break::GXWrapper;

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glew32.lib")

void GLManager::applyFilter2D(TextureFilter filter, bool mipmap,GLenum target)
{
	switch (filter)
	{
	case TextureFilter::POINT:
		if(mipmap)
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
		else
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		break;
	case TextureFilter::LINEAR:
		if(mipmap)
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		else
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		break;
	case TextureFilter::ANISOTROPIC:
		if(mipmap)
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		else
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		break;
	case TextureFilter::LINEAR_MIP_POINT:
		if(mipmap)
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		else
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		break;
	case TextureFilter::POINT_MIP_LINEAR:
		if(mipmap)
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
		else
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		break;
	case TextureFilter::MIN_LINEAR_MAG_POINT_MIP_LINEAR:
		if(mipmap)
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		else
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		break;
	case TextureFilter::MIN_LINEAR_MAG_POINT_MIP_POINT:
		if(mipmap)
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		else
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		break;
	case TextureFilter::MIN_POINT_MAG_LINEAR_MIP_LINEAR:
		if(mipmap)
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
		else
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		break;
	case TextureFilter::MIN_POINT_MAG_LINEAR_MIP_POINT:
		if(mipmap)
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
		else
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		break;
	default: break;
	}
}

int GLManager::getAddressMode(TextureAddressMode mode)
{
	switch (mode)
	{
	case TextureAddressMode::WRAP:
		return GL_REPEAT;
		break;
	case TextureAddressMode::CLAMP:
		return GL_CLAMP_TO_EDGE;
		break;
	case TextureAddressMode::MIRROR:
		return GL_MIRRORED_REPEAT;
		break;
	case TextureAddressMode::BORDER:
		return GL_CLAMP_TO_BORDER;
		break;
	default:
		return -1;
		break;
	}
}

int GLManager::getCompareFunc(CompareFunction func)
{
	switch (func)
	{
	case CompareFunction::ALWAYS:
		return GL_ALWAYS;
		break;
	case CompareFunction::NEVER:
		return GL_NEVER;
		break;
	case CompareFunction::LESS:
		return GL_LESS;
		break;
	case CompareFunction::LESS_EQUAL:
		return GL_LEQUAL;
		break;
	case CompareFunction::EQUAL:
		return GL_EQUAL;
		break;
	case CompareFunction::GREATER_EQUAL:
		return GL_GEQUAL;
		break;
	case CompareFunction::GREATER:
		return GL_GREATER;
		break;
	case CompareFunction::NOT_EQUAL:
		return GL_NOTEQUAL;
		break;
	default: break;
	}
}

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
	window = glfwCreateWindow(app->display->getWidth(), app->display->getHeight(),app->display->getTitle().c_str() , NULL, NULL);
	if( window == nullptr ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
	glewExperimental=true; // Needed in core profile 
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);
	glEnable(GL_RGBA);
	glEnable(GL_DOUBLE);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glPointSize(5);

	//glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);

	Display<GLFWwindow*>* d = new Display<GLFWwindow*>(*app->display);
	d->setHandle(window);
	app->display = IDisplayPtr(d);
	return true;
}

void GLManager::start(){
	Display<GLFWwindow*>* d = dynamic_cast<Display<GLFWwindow*>*>(Engine::Instance->Application->display.get());
	glfwSetKeyCallback(d->getHandle(),&Input::GLKeyboard::keyboardFunc);
	glfwSetMouseButtonCallback(d->getHandle(),&Input::GLMouse::mouseFunc);
	glfwSetCursorPosCallback(d->getHandle(),&Input::GLMouse::mouseMotion);
	while(!glfwWindowShouldClose(d->getHandle())){
		Engine::Instance->gameloop();
		//check if the engine is shutting down
		if(Engine::Instance->_shutdown)
			break;
		glfwPollEvents();
		//glfwWaitEvents();
	}
	d = NULL;
	return;
}

void GLManager::setRasterMode(RasterMode mode)
{
	//this is my Saad comment 

	switch (mode)
	{
	case RasterMode::FILL: 
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		break;
	case RasterMode::WIREFRAME:
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		break;
	default: break;
	}
}

void GLManager::setCullMode(CullMode mode)
{
	switch (mode)
	{
	case CullMode::NONE: 
		glDisable(GL_CULL_FACE);
		break;
	case CullMode::FRONT:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	case CullMode::BACK: 
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	default: break;
	}
}

void GLManager::clearBuffer(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLManager::swapBuffer(){
	Display<GLFWwindow*>* d = dynamic_cast<Display<GLFWwindow*>*>(Engine::Instance->Application->display.get());
	glfwSwapBuffers(d->getHandle());
	d = NULL;
}

void GLManager::setCursorPostion(glm::uvec2 val){
	Display<GLFWwindow*>* d = dynamic_cast<Display<GLFWwindow*>*>(Engine::Instance->Application->display.get());
	glfwSetCursorPos(d->getHandle(),(double)val.x,(double)val.y);
	d = NULL;
}

bool GLManager::createVertexBuffer(GPUResource* buffer){

	GXWrapper::VertexBuffer* VBuffer = dynamic_cast<GXWrapper::VertexBuffer*>(buffer);

	auto handle = make_shared<GLHandle>();
	
	GLuint id;
	glGenBuffers(1,&id);
	glBindBuffer(GL_ARRAY_BUFFER,id);
	
	
	switch ((int)VBuffer->getType())
	{

	//static
	case 1:
		glBufferData(GL_ARRAY_BUFFER,VBuffer->getSize(),VBuffer->getData(),GL_STATIC_DRAW);
		break;

	//dynamic
	case 0:
		glBufferData(GL_ARRAY_BUFFER,VBuffer->getSize(),VBuffer->getData(),GL_DYNAMIC_DRAW);
		break;

	default:
		return false;
		break;
	}

	handle->ID = id;

	VBuffer->_handle = handle;
	glBindBuffer(GL_ARRAY_BUFFER,0);
	return true;
}

Infrastructure::IGPUHandlePtr GLManager::vm_createVertexBuffer(Renderer::GPU_ISA type, u32 size, void* data)
{

	auto handle = make_shared<GLHandle>();
	
	GLuint id = -1;
	glGenBuffers(1,&id);
	if (id == -1)
		throw GPUException("Cannot generate vertex buffer");
	glBindBuffer(GL_ARRAY_BUFFER,id);
	
	
	switch (type)
	{

	//static
	case GPU_ISA::STATIC:
		glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
		break;

	//dynamic
	case GPU_ISA::DYNAMIC:
		glBufferData(GL_ARRAY_BUFFER,size,data,GL_DYNAMIC_DRAW);
		break;

	default:
		return nullptr;
		break;
	}

	handle->ID = id;

	glBindBuffer(GL_ARRAY_BUFFER,0);
	return handle;
}

bool GLManager::createIndexBuffer(GPUResource* buffer){
	GXWrapper::IndexBuffer* IBuffer = dynamic_cast<GXWrapper::IndexBuffer*>(buffer);

	auto handle = make_shared<GLHandle>();

	GLuint id;
	glGenBuffers(1,&id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);

	switch ((int)IBuffer->getType())
	{

		//static
	case 1:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,IBuffer->getSize(),IBuffer->getData(),GL_STATIC_DRAW);
		break;

		//dynamic
	case 0:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,IBuffer->getSize(),IBuffer->getData(),GL_DYNAMIC_DRAW);
		break;

	default:
		return false;
		break;
	}

	handle->ID = id;

	IBuffer->_handle = handle;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	return true;
}

Infrastructure::IGPUHandlePtr GLManager::vm_createIndexBuffer(Renderer::GPU_ISA type, u32 size, void* data)
{

	auto handle = make_shared<GLHandle>();

	GLuint id=-1;
	glGenBuffers(1,&id);
	if (id == -1)
		throw GPUException("Cannot generate index buffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);

	switch (type)
	{

		//static
	case GPU_ISA::STATIC:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
		break;
		//dynamic
	case GPU_ISA::DYNAMIC:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data,GL_DYNAMIC_DRAW);
		break;

	default:
		return nullptr;
		break;
	}

	handle->ID = id;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	return handle;
}

bool GLManager::updateVertexBuffer(GPUResource* buffer, unsigned int offset, unsigned int size){
	GXWrapper::VertexBuffer* VBuffer = dynamic_cast<GXWrapper::VertexBuffer*>(buffer);

	if(VBuffer->getType() == VertexBuffer::STATIC)
		throw GPUException("Cannot Map Vertex Buffer: Buffer type is not dynamic");

	auto handle = dynamic_cast<GLHandle*>(VBuffer->_handle.get());

	glBindBuffer(GL_ARRAY_BUFFER,handle->ID);
	//glBufferData(GL_ARRAY_BUFFER,VBuffer->getSize(),NULL,GL_DYNAMIC_DRAW);
	void* GPUPtr = NULL;
	GPUPtr = glMapBufferRange(GL_ARRAY_BUFFER,offset,size,GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_RANGE_BIT );

	if(GPUPtr == NULL)
		throw GXWrapper::GPUException("Cannot Map Vertex Buffer: Failed to get buffer pointer");

	memcpy(GPUPtr,VBuffer->getData(offset),size);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	return true;
}

void GLManager::vm_mapVertexBuffer(Infrastructure::IGPUHandle* _handle, u32 size, void* data)
{

	auto handle = dynamic_cast<GLHandle*>(_handle);

	glBindBuffer(GL_ARRAY_BUFFER,handle->ID);
	//glBufferData(GL_ARRAY_BUFFER,VBuffer->getSize(),NULL,GL_DYNAMIC_DRAW);
	void* GPUPtr = NULL;
	GPUPtr = glMapBufferRange(GL_ARRAY_BUFFER,0,size,GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_RANGE_BIT );

	if(GPUPtr == NULL)
		throw GXWrapper::GPUException("Cannot Map Vertex Buffer: Failed to get buffer pointer");

	memcpy(GPUPtr,data,size);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER,0);
}

bool GLManager::updateIndexBuffer(GPUResource* buffer, unsigned int offset, unsigned int size){
	auto IBuffer = dynamic_cast<GXWrapper::IndexBuffer*>(buffer);

	if(IBuffer->getType() == VertexBuffer::STATIC)
		throw GPUException("Cannot Map Index Buffer: Buffer type is not dynamic");

	auto handle = dynamic_cast<GLHandle*>(IBuffer->_handle.get());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,handle->ID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,IBuffer->getSize(),NULL,GL_DYNAMIC_DRAW);
	void* GPUPtr = NULL;
	GPUPtr = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER,offset,size,GL_MAP_WRITE_BIT |GL_MAP_INVALIDATE_RANGE_BIT );

	if(GPUPtr == NULL)
		throw GXWrapper::GPUException("Cannot Map Index Buffer: Failed to get buffer pointer");

	memcpy(GPUPtr,IBuffer->getData(offset),size);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	return true;
}

void GLManager::vm_mapIndexBuffer(Infrastructure::IGPUHandle* _handle, u32 size, void* data)
{

	auto handle = dynamic_cast<GLHandle*>(_handle);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,handle->ID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,IBuffer->getSize(),NULL,GL_DYNAMIC_DRAW);
	void* GPUPtr = NULL;
	GPUPtr = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER,0,size,GL_MAP_WRITE_BIT |GL_MAP_INVALIDATE_RANGE_BIT );

	if(GPUPtr == NULL)
		throw GXWrapper::GPUException("Cannot Map Index Buffer: Failed to get buffer pointer");

	memcpy(GPUPtr,data,size);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

bool GLManager::deleteBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<GLHandle*>(buffer->_handle.get());
	glDeleteBuffers(1,&handle->ID);
	return true;
}

bool GLManager::vm_deleteBuffer(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<GLHandle*>(_handle);
	glDeleteBuffers(1,&handle->ID);
	return true;
}

bool GLManager::useVertexBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<GLHandle*>(buffer->_handle.get());

	glBindBuffer(GL_ARRAY_BUFFER,handle->ID);
	return true;
}

void GLManager::vm_bindVertexBuffer(Infrastructure::IGPUHandle* _handle, u32 stride)
{
	auto handle = dynamic_cast<GLHandle*>(_handle);

	glBindBuffer(GL_ARRAY_BUFFER,handle->ID);
}

bool GLManager::useIndexBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<GLHandle*>(buffer->_handle.get());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,handle->ID);
	return true;
}

void GLManager::vm_bindIndexBuffer(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<GLHandle*>(_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,handle->ID);
}

bool GLManager::createShader(GPUResource* shader){
	auto program = dynamic_cast<GXWrapper::Shader*>(shader);

	auto handle = make_shared<GLShaderHandle>();

	handle->vertexShader = glCreateShader(GL_VERTEX_SHADER);

	char* error = new char[1024];
	const GLchar* p[1];
	p[0] = program->_vs.c_str();
	GLint lengths[1];
	lengths[0] = program->_vs.size();
	glShaderSource(handle->vertexShader,1,p,lengths);
	glCompileShader(handle->vertexShader);

	GLint res = 0;
	glGetShaderiv(handle->vertexShader,GL_COMPILE_STATUS,&res);

	if(res == GL_FALSE){
		glGetShaderInfoLog(handle->vertexShader,1024,NULL,error);
		std::cout<<error<<std::endl;
		return false;
	}

	handle->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);

	p[0] = program->_ps.c_str();
	lengths[0] = program->_ps.size();

	glShaderSource(handle->pixelShader,1,p,lengths);
	glCompileShader(handle->pixelShader);

	glGetShaderiv(handle->pixelShader,GL_COMPILE_STATUS,&res);

	if(res == GL_FALSE){
		glGetShaderInfoLog(handle->pixelShader,1024,NULL,error);
		std::cout<<error<<std::endl;
		return false;
	}

	handle->program = glCreateProgram();

	glAttachShader(handle->program,handle->vertexShader);
	glAttachShader(handle->program,handle->pixelShader);

	glLinkProgram(handle->program);
	glGetProgramiv(handle->program,GL_LINK_STATUS,&res);

	if(res == GL_FALSE){
		glGetProgramInfoLog(handle->program,1024,NULL,error);
		std::cout<<error<<std::endl;
		return false;
	}
	glValidateProgram(handle->program);
	glGetProgramiv(handle->program,GL_VALIDATE_STATUS,&res);

	if(res == GL_FALSE){
		glGetProgramInfoLog(handle->program,1024,NULL,error);
		std::cout<<error<<std::endl;
		return false;
	}

	program->_handle = handle;
	delete[] error;
	return true;
}

Infrastructure::IGPUHandlePtr GLManager::vm_createProgram(std::string vertex, std::string pixel, GXWrapper::MemoryLayout* inputLayout)
{

	auto handle = make_shared<GLShaderHandle>();

	handle->vertexShader = glCreateShader(GL_VERTEX_SHADER);

	char* error = new char[1024];
	const GLchar* p[1];
	p[0] = vertex.c_str();
	GLint lengths[1];
	lengths[0] = vertex.size();
	glShaderSource(handle->vertexShader,1,p,lengths);
	glCompileShader(handle->vertexShader);

	GLint res = 0;
	glGetShaderiv(handle->vertexShader,GL_COMPILE_STATUS,&res);

	if(res == GL_FALSE){
		glGetShaderInfoLog(handle->vertexShader,1024,NULL,error);
		std::cout<<error<<std::endl;
		throw GPUException("Cannot compile vertex shader");
	}

	handle->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);

	p[0] = pixel.c_str();
	lengths[0] = pixel.size();

	glShaderSource(handle->pixelShader,1,p,lengths);
	glCompileShader(handle->pixelShader);

	glGetShaderiv(handle->pixelShader,GL_COMPILE_STATUS,&res);

	if(res == GL_FALSE){
		glGetShaderInfoLog(handle->pixelShader,1024,NULL,error);
		std::cout<<error<<std::endl;
		throw GPUException("Cannot compile pixel shader");
	}

	handle->program = glCreateProgram();

	glAttachShader(handle->program,handle->vertexShader);
	glAttachShader(handle->program,handle->pixelShader);

	glLinkProgram(handle->program);
	glGetProgramiv(handle->program,GL_LINK_STATUS,&res);

	if(res == GL_FALSE){
		glGetProgramInfoLog(handle->program,1024,NULL,error);
		std::cout<<error<<std::endl;
		throw GPUException("Cannot link GPU program");
	}
	glValidateProgram(handle->program);
	glGetProgramiv(handle->program,GL_VALIDATE_STATUS,&res);

	if(res == GL_FALSE){
		glGetProgramInfoLog(handle->program,1024,NULL,error);
		std::cout<<error<<std::endl;
		throw GPUException("GPU program validation error");
	}

	delete[] error;
	return handle;
}

bool GLManager::deleteShader(GPUResource* shader){
	auto handle = dynamic_cast<GLShaderHandle*>(shader->_handle.get());

	if(handle->vertexShader)
		glDeleteShader(handle->vertexShader);
	if(handle->pixelShader)
		glDeleteShader(handle->pixelShader);
	if(handle->program)
		glDeleteProgram(handle->program);

	return true;
}

void GLManager::vm_deleteShader(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<GLShaderHandle*>(_handle);

	if(handle->vertexShader)
		glDeleteShader(handle->vertexShader);
	if(handle->pixelShader)
		glDeleteShader(handle->pixelShader);
	if(handle->program)
		glDeleteProgram(handle->program);
}

bool GLManager::useShader(GPUResource* shader){
	auto handle = dynamic_cast<GLShaderHandle*>(shader->_handle.get());

	glUseProgram(handle->program);

	return true;
}

void GLManager::vm_bindShader(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<GLShaderHandle*>(_handle);

	glUseProgram(handle->program);
}

bool GLManager::createUniformBuffer(GPUResource* buffer){
	auto UBuffer = dynamic_cast<GXWrapper::UniformBuffer*>(buffer);

	auto handle = make_shared<GLHandle>();

	glGenBuffers(1,&handle->ID);
	glBindBuffer(GL_UNIFORM_BUFFER,handle->ID);
	glBufferData(GL_UNIFORM_BUFFER,UBuffer->getSize(),UBuffer->getData(),GL_DYNAMIC_DRAW);

	glBindBufferBase(GL_UNIFORM_BUFFER,UBuffer->_slot,handle->ID);

	glBindBuffer(GL_UNIFORM_BUFFER,0);

	buffer->_handle = handle;
	return true;
}

Infrastructure::IGPUHandlePtr GLManager::vm_createUniformBuffer(u32 size, void* data, u32 slot)
{

	auto handle = make_shared<GLHandle>();

	glGenBuffers(1,&handle->ID);
	glBindBuffer(GL_UNIFORM_BUFFER,handle->ID);
	glBufferData(GL_UNIFORM_BUFFER,size,data,GL_DYNAMIC_DRAW);

	glBindBufferBase(GL_UNIFORM_BUFFER,slot,handle->ID);

	glBindBuffer(GL_UNIFORM_BUFFER,0);

	return handle;
}

bool GLManager::updateUniformBuffer(GPUResource* buffer,unsigned int offset,unsigned int size){
	auto UBuffer = dynamic_cast<GXWrapper::UniformBuffer*>(buffer);


	auto handle = dynamic_cast<GLHandle*>(UBuffer->_handle.get());

	glBindBuffer(GL_UNIFORM_BUFFER,handle->ID);
	//glBufferData(GL_UNIFORM_BUFFER,UBuffer->getSize(),NULL,GL_DYNAMIC_DRAW);
	void* GPUPtr = NULL;
	GPUPtr = glMapBufferRange(GL_UNIFORM_BUFFER,offset,size,GL_MAP_WRITE_BIT |GL_MAP_INVALIDATE_RANGE_BIT );

	if(GPUPtr == NULL)
		throw GXWrapper::GPUException("Cannot Map Index Buffer: Failed to get buffer pointer");

	memcpy(GPUPtr,UBuffer->getData(offset),size);
	glUnmapBuffer(GL_UNIFORM_BUFFER);

	glBindBuffer(GL_UNIFORM_BUFFER,0);
	return true;
}

void GLManager::vm_mapUniformBuffer(Infrastructure::IGPUHandle* _handle, u32 size, void* data)
{

	auto handle = dynamic_cast<GLHandle*>(_handle);

	glBindBuffer(GL_UNIFORM_BUFFER,handle->ID);
	//glBufferData(GL_UNIFORM_BUFFER,UBuffer->getSize(),NULL,GL_DYNAMIC_DRAW);
	void* GPUPtr = NULL;
	GPUPtr = glMapBufferRange(GL_UNIFORM_BUFFER,0,size,GL_MAP_WRITE_BIT |GL_MAP_INVALIDATE_RANGE_BIT );

	if(GPUPtr == NULL)
		throw GXWrapper::GPUException("Cannot Map Uniform Buffer: Failed to get buffer pointer");

	memcpy(GPUPtr,data,size);
	glUnmapBuffer(GL_UNIFORM_BUFFER);

	glBindBuffer(GL_UNIFORM_BUFFER,0);
}

bool GLManager::useUniformBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<GLHandle*>(buffer->_handle.get());
	auto UBuffer = dynamic_cast<GXWrapper::UniformBuffer*>(buffer);
	glBindBuffer(GL_UNIFORM_BUFFER,handle->ID);
	glBindBufferBase(GL_UNIFORM_BUFFER,UBuffer->_slot,handle->ID);
	return true;
}

void GLManager::vm_bindUniformBuffer(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA shader, u32 slot)
{
	auto handle = dynamic_cast<GLHandle*>(_handle);
	glBindBuffer(GL_UNIFORM_BUFFER,handle->ID);
	glBindBufferBase(GL_UNIFORM_BUFFER,slot,handle->ID);
}

bool GLManager::createTexture2D(GPUResource* texture,Image& img){
	auto tex = dynamic_cast<Texture2D*>(texture);

	auto handle = make_shared<GLHandle>();

	glGenTextures(1,&handle->ID);
	glBindTexture(GL_TEXTURE_2D,handle->ID);

		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getWidth(),img.getHeight(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.getPixels());
		if(tex->usingMipMaps())
			glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,0);
	tex->_handle = handle;
	return true;
}

Infrastructure::IGPUHandlePtr GLManager::vm_createTexture2D(GXWrapper::Image& img, bool mipmaps)
{
	auto handle = make_shared<GLHandle>();

	glGenTextures(1,&handle->ID);
	glBindTexture(GL_TEXTURE_2D,handle->ID);

		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getWidth(),img.getHeight(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.getPixels());
		if(mipmaps)
			glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,0);
	return handle;
}

bool GLManager::updateTexture2D(GPUResource* texture,Image& img){
	auto handle = dynamic_cast<GLHandle*>(texture->_handle.get());

	glBindTexture(GL_TEXTURE_2D,handle->ID);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getWidth(),img.getHeight(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.getPixels());
	glBindTexture(GL_TEXTURE_2D,0);
	return true;
}

void GLManager::vm_mapTexture2D(Infrastructure::IGPUHandle* _handle, GXWrapper::Image& img)
{
	auto handle = dynamic_cast<GLHandle*>(_handle);

	glBindTexture(GL_TEXTURE_2D,handle->ID);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getWidth(),img.getHeight(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.getPixels());
	glBindTexture(GL_TEXTURE_2D,0);
	
}

bool GLManager::deleteTexture2D(GPUResource* texture){
	auto handle = dynamic_cast<GLHandle*>(texture->_handle.get());

	glDeleteTextures(1,&handle->ID);

	return true;
}

void GLManager::vm_deleteTexture2D(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<GLHandle*>(_handle);

	glDeleteTextures(1,&handle->ID);
}

bool GLManager::useTexture2D(GPUResource* texture, unsigned int unit, Shader::Type)
{
	auto handle = dynamic_cast<GLHandle*>(texture->_handle.get());

	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D,handle->ID);

	return true;
}

void GLManager::vm_bindTexture2D(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA type, u32 unit)
{
	auto handle = dynamic_cast<GLHandle*>(_handle);

	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D,handle->ID);
}

bool GLManager::createGeometry(Geometry* geometry)
{
	auto geo = geometry;

	auto handle = make_shared<GLHandle>();

	glGenVertexArrays(1,&handle->ID);
	glBindVertexArray(handle->ID);

	geo->_geometryData.vertices->use();
	
	MemoryLayout layout = geo->getMemoryLayout();

	for(int i=0;i<layout.getElementCount();i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,layout.elements[i].components,GL_FLOAT,GL_FALSE,layout.getSize(),reinterpret_cast<void*>(layout.elements[i].offset));
	}
	if(geo->_geometryData.indices)
		geo->_geometryData.indices->use();

	glBindVertexArray(0);

	geo->_handle = handle;
	return true;
}

Infrastructure::IGPUHandlePtr GLManager::vm_createGeometry(Infrastructure::IGPUHandle* vertex, Infrastructure::IGPUHandle* index, GXWrapper::MemoryLayout* input_layout)
{

	auto handle = make_shared<GLHandle>();

	glGenVertexArrays(1,&handle->ID);
	glBindVertexArray(handle->ID);

	//geo->_geometryData.vertices->use();
	vm_bindVertexBuffer(vertex,input_layout->getSize());
	
	MemoryLayout layout = *input_layout;

	for(int i=0;i<layout.getElementCount();i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,layout.elements[i].components,GL_FLOAT,GL_FALSE,layout.getSize(),reinterpret_cast<void*>(layout.elements[i].offset));
	}
	if(index)
		vm_bindIndexBuffer(index);

	glBindVertexArray(0);

	
	return handle;
}

bool GLManager::drawGeometry(Geometry* geometry, Primitive::Mode mode)
{
	auto geo = (geometry);

	auto handle = dynamic_cast<GLHandle*>(geo->_handle.get());

	glBindVertexArray(handle->ID);

	auto geoData = geo->_geometryData;
		
	geoData.primitive;

	switch ((int)mode)
	{
	case Primitive::NORMAL:       /*normal drawing*/
		geoData.vertices->use();
		if(geoData.primitive == 0)
			glDrawArrays(GL_POINTS,0,geoData.verticesCount);

		if(geoData.primitive == 1)
			glDrawArrays(GL_LINES,0,geoData.verticesCount);

		if(geoData.primitive == 2)
			glDrawArrays(GL_LINE_STRIP,0,geoData.verticesCount);

		if(geoData.primitive == 3)
			glDrawArrays(GL_LINE_LOOP,0,geoData.verticesCount);

		if(geoData.primitive == 4)
			glDrawArrays(GL_TRIANGLES,0,geoData.verticesCount);

		if(geoData.primitive == 5)
			glDrawArrays(GL_TRIANGLE_STRIP,0,geoData.verticesCount);

		if(geoData.primitive == 6)
			glDrawArrays(GL_TRIANGLE_FAN,0,geoData.verticesCount);

		break;


	case 1:       /*indexed drawing*/

		geoData.vertices->use();
		geoData.indices->use();
		if(geoData.primitive == 0)
			glDrawElements(GL_POINTS , geoData.indicesCount , GL_UNSIGNED_INT ,(void*)0);

		if(geoData.primitive == 1)
			glDrawElements(GL_LINES , geoData.indicesCount , GL_UNSIGNED_INT ,(void*)0);

		if(geoData.primitive == 2)
			glDrawElements(GL_LINE_STRIP , geoData.indicesCount , GL_UNSIGNED_INT ,(void*)0);

		if(geoData.primitive == 3)
			glDrawElements(GL_LINE_LOOP , geoData.indicesCount , GL_UNSIGNED_INT ,(void*)0);

		if(geoData.primitive == 4)
			glDrawElements(GL_TRIANGLES , geoData.indicesCount , GL_UNSIGNED_INT ,(void*)0);

		if(geoData.primitive == 5)
			glDrawElements(GL_TRIANGLE_STRIP , geoData.indicesCount , GL_UNSIGNED_INT ,(void*)0);

		if(geoData.primitive == 6)
			glDrawElements(GL_TRIANGLE_FAN , geoData.indicesCount , GL_UNSIGNED_INT ,(void*)0);

		break;

	case 2:      /*normal instanced drawing*/
		if(geoData.primitive == 0)
			glDrawArraysInstanced(GL_POINTS ,0, geoData.verticesCount ,geoData.instanceCount);

		if(geoData.primitive == 1)
			glDrawArraysInstanced(GL_LINES ,0, geoData.verticesCount ,geoData.instanceCount);

		if(geoData.primitive == 2)
			glDrawArraysInstanced(GL_LINE_STRIP ,0, geoData.verticesCount ,geoData.instanceCount);

		if(geoData.primitive == 3)
			glDrawArraysInstanced(GL_LINE_LOOP ,0, geoData.verticesCount ,geoData.instanceCount);

		if(geoData.primitive == 4)
			glDrawArraysInstanced(GL_TRIANGLES ,0, geoData.verticesCount ,geoData.instanceCount);

		if(geoData.primitive == 5)
			glDrawArraysInstanced(GL_TRIANGLE_STRIP ,0, geoData.verticesCount ,geoData.instanceCount);

		if(geoData.primitive == 6)
			glDrawArraysInstanced(GL_TRIANGLE_FAN ,0, geoData.verticesCount ,geoData.instanceCount);

		break;

	case 3:      /*index instanced drawing*/
		if(geoData.primitive == 0)
			glDrawElementsInstanced(GL_POINTS , geoData.indicesCount, GL_UNSIGNED_INT ,(void*)0 ,geoData.instanceCount);

		if(geoData.primitive == 1)
			glDrawElementsInstanced(GL_LINES , geoData.indicesCount, GL_UNSIGNED_INT ,(void*)0 ,geoData.instanceCount);

		if(geoData.primitive == 2)
			glDrawElementsInstanced(GL_LINE_STRIP , geoData.indicesCount, GL_UNSIGNED_INT ,(void*)0 ,geoData.instanceCount);

		if(geoData.primitive == 3)
			glDrawElementsInstanced(GL_LINE_LOOP , geoData.indicesCount, GL_UNSIGNED_INT ,(void*)0 ,geoData.instanceCount);

		if(geoData.primitive == 4)
			glDrawElementsInstanced(GL_TRIANGLES , geoData.indicesCount, GL_UNSIGNED_INT ,(void*)0 ,geoData.instanceCount);

		if(geoData.primitive == 5)
			glDrawElementsInstanced(GL_TRIANGLE_STRIP , geoData.indicesCount , GL_UNSIGNED_INT ,(void*)0 ,geoData.instanceCount);

		if(geoData.primitive == 6)
			glDrawElementsInstanced(GL_TRIANGLE_FAN , geoData.indicesCount, GL_UNSIGNED_INT ,(void*)0 ,geoData.instanceCount);

		break;
	}
	return true;
}

void GLManager::vm_draw(GXWrapper::Primitive::Type type,Infrastructure::IGPUHandle* geometry_handle,
						Infrastructure::IGPUHandle* vertex_buffer, u32 vertices_count,
						GXWrapper::MemoryLayout* input_layout)
{

	auto handle = dynamic_cast<GLHandle*>(geometry_handle);

	glBindVertexArray(handle->ID);

	vm_bindVertexBuffer(vertex_buffer,input_layout->getSize());
		if(type == 0)
			glDrawArrays(GL_POINTS,0,vertices_count);
		else if(type == 1)
			glDrawArrays(GL_LINES,0,vertices_count);
		else if(type == 2)
			glDrawArrays(GL_LINE_STRIP,0,vertices_count);
		else if(type == 3)
			glDrawArrays(GL_LINE_LOOP,0,vertices_count);
		else if(type == 4)
			glDrawArrays(GL_TRIANGLES,0,vertices_count);
		else if(type == 5)
			glDrawArrays(GL_TRIANGLE_STRIP,0,vertices_count);
		else if(type == 6)
			glDrawArrays(GL_TRIANGLE_FAN,0,vertices_count);
		else
			throw GPUException("Cannot identify primitive type");

}

void GLManager::vm_drawIndexed(GXWrapper::Primitive::Type type, Infrastructure::IGPUHandle* geometry, Infrastructure::IGPUHandle* vertex_buffer, Infrastructure::IGPUHandle* index_buffer, u32 indices_count, GXWrapper::MemoryLayout* input_layout)
{

	auto handle = dynamic_cast<GLHandle*>(geometry);

	glBindVertexArray(handle->ID);

	vm_bindVertexBuffer(vertex_buffer,input_layout->getSize());

	vm_bindIndexBuffer(index_buffer);
	if(type == 0)
		glDrawElements(GL_POINTS , indices_count , GL_UNSIGNED_INT ,(void*)0);
	else if(type == 1)
		glDrawElements(GL_LINES , indices_count , GL_UNSIGNED_INT ,(void*)0);

	else if(type == 2)
		glDrawElements(GL_LINE_STRIP , indices_count , GL_UNSIGNED_INT ,(void*)0);

	else if(type == 3)
		glDrawElements(GL_LINE_LOOP , indices_count , GL_UNSIGNED_INT ,(void*)0);

	else if(type == 4)
		glDrawElements(GL_TRIANGLES , indices_count , GL_UNSIGNED_INT ,(void*)0);

	else if(type == 5)
		glDrawElements(GL_TRIANGLE_STRIP , indices_count , GL_UNSIGNED_INT ,(void*)0);

	else if(type == 6)
		glDrawElements(GL_TRIANGLE_FAN , indices_count , GL_UNSIGNED_INT ,(void*)0);
	else
		throw GPUException("Cannot identify primitive type");
}

bool GLManager::deleteGeometry(GPUResource* geometry)
{
	auto handle = dynamic_cast<GLHandle*>(geometry->_handle.get());

	glDeleteVertexArrays(1,&handle->ID);

	return true;
}

void GLManager::vm_deleteGeometry(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<GLHandle*>(_handle);

	glDeleteVertexArrays(1,&handle->ID);
}

bool GLManager::createSamplerState(GPUResource*)
{
	return true;
}

Infrastructure::IGPUHandlePtr GLManager::vm_createSampleState(GXWrapper::TextureAddressMode U, GXWrapper::TextureAddressMode V, GXWrapper::TextureAddressMode W, GXWrapper::TextureFilter filter, GXWrapper::CompareFunction func, GXWrapper::Color* color)
{
	return make_shared<GLHandle>();
}

bool GLManager::useSamplerState(GPUResource*, unsigned slot, Shader::Type type)
{
	return true;
}

void GLManager::vm_bindSampler(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA shader, u32 slot)
{
	return;
}

bool GLManager::deleteSamplerState(GPUResource*)
{
	return true;
}

void GLManager::vm_deleteSampler(Infrastructure::IGPUHandle* _handle)
{
	return;
}

bool GLManager::applySamplerStateToTexture2D(GPUResource* gpSampler, GPUResource* texture)
{
	auto texHandle = dynamic_cast<GLHandle*>(texture->_handle.get());
	auto tex = dynamic_cast<Texture*>(texture);
	auto sampler = dynamic_cast<SamplerState*>(gpSampler);


	if(tex->getType() == Texture::TEXTURE2D){
		glBindTexture(GL_TEXTURE_2D,texHandle->ID);
		applyFilter2D(sampler->filter,tex->usingMipMaps(),GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,getAddressMode(sampler->addressU));
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,getAddressMode(sampler->addressV));
		float border[4] = {sampler->borderColor.R,sampler->borderColor.G,sampler->borderColor.B,sampler->borderColor.A};
		glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,border);
		if(sampler->compareFunction != GXWrapper::CompareFunction::NEVER)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,getCompareFunc(sampler->compareFunction));
		glBindTexture(GL_TEXTURE_2D,0);
	}
	else
		return false;

	return true;

}

void GLManager::vm_applySamplerTexture2D(Infrastructure::IGPUHandle* sampler, Infrastructure::IGPUHandle* texture, bool mipmaps, GXWrapper::TextureAddressMode U, GXWrapper::TextureAddressMode V, GXWrapper::TextureFilter filter, GXWrapper::CompareFunction func, GXWrapper::Color border_color)
{
	auto texHandle = dynamic_cast<GLHandle*>(texture);

		glBindTexture(GL_TEXTURE_2D,texHandle->ID);
		applyFilter2D(filter,mipmaps,GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,getAddressMode(U));
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,getAddressMode(V));
		float border[4] = {border_color.R,border_color.G,border_color.B,border_color.A};
		glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,border);
		if(func != GXWrapper::CompareFunction::NEVER)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,getCompareFunc(func));
		glBindTexture(GL_TEXTURE_2D,0);
}