#include "GLManager.h"
#include <GL/glew.h>
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
using namespace std;
using namespace Break::Renderer;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glew32.lib")

void GLManager::applyFilter2D(TextureFilter filter, bool mipmap,GLHandle* tex)
{
	switch (filter)
	{
	case TextureFilter::POINT:
		if(mipmap)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
		else
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		break;
	case TextureFilter::LINEAR:
		if(mipmap)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		else
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		break;
	case TextureFilter::ANISOTROPIC:
		if(mipmap)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		else
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		break;
	case TextureFilter::LINEAR_MIP_POINT:
		if(mipmap)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		else
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		break;
	case TextureFilter::POINT_MIP_LINEAR:
		if(mipmap)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
		else
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		break;
	case TextureFilter::MIN_LINEAR_MAG_POINT_MIP_LINEAR:
		if(mipmap)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		else
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		break;
	case TextureFilter::MIN_LINEAR_MAG_POINT_MIP_POINT:
		if(mipmap)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		else
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		break;
	case TextureFilter::MIN_POINT_MAG_LINEAR_MIP_LINEAR:
		if(mipmap)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
		else
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		break;
	case TextureFilter::MIN_POINT_MAG_LINEAR_MIP_POINT:
		if(mipmap)
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
		else
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
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
	default: break;
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
		//check if the engine is shutting down
		if(Engine::Instance->_shutdown)
			break;
		glfwPollEvents();
		//glfwWaitEvents();
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

bool GLManager::createVertexBuffer(GPUResource* buffer){

	GXWrapper::VertexBuffer* VBuffer = dynamic_cast<GXWrapper::VertexBuffer*>(buffer);

	auto handle = make_shared<GLHandle>();
	
	GLuint id;
	glGenBuffers(1,&id);
	glBindBuffer(GL_ARRAY_BUFFER,id);
	
	
	switch (VBuffer->getType())
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

bool GLManager::createIndexBuffer(GPUResource* buffer){
	GXWrapper::IndexBuffer* IBuffer = dynamic_cast<GXWrapper::IndexBuffer*>(buffer);

	auto handle = make_shared<GLHandle>();

	GLuint id;
	glGenBuffers(1,&id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);

	switch (IBuffer->getType())
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

bool GLManager::updateVertexBuffer(GPUResource* buffer, unsigned int offset, unsigned int size){
	GXWrapper::VertexBuffer* VBuffer = dynamic_cast<GXWrapper::VertexBuffer*>(buffer);

	if(VBuffer->getType() == VertexBuffer::STATIC)
		throw GPUException("Cannot Map Vertex Buffer: Buffer type is not dynamic");

	auto handle = dynamic_cast<GLHandle*>(VBuffer->_handle.get());

	glBindBuffer(GL_ARRAY_BUFFER,handle->ID);
	void* GPUPtr = NULL;
	GPUPtr = glMapBufferRange(GL_ARRAY_BUFFER,offset,size,GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	if(GPUPtr == NULL)
		throw GXWrapper::GPUException("Cannot Map Vertex Buffer: Failed to get buffer pointer");

	memcpy(GPUPtr,VBuffer->getData(offset),size);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	return true;
}

bool GLManager::updateIndexBuffer(GPUResource* buffer, unsigned int offset, unsigned int size){
	auto IBuffer = dynamic_cast<GXWrapper::IndexBuffer*>(buffer);

	if(IBuffer->getType() == VertexBuffer::STATIC)
		throw GPUException("Cannot Map Index Buffer: Buffer type is not dynamic");

	auto handle = dynamic_cast<GLHandle*>(IBuffer->_handle.get());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,handle->ID);
	void* GPUPtr = NULL;
	GPUPtr = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER,offset,size,GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	if(GPUPtr == NULL)
		throw GXWrapper::GPUException("Cannot Map Index Buffer: Failed to get buffer pointer");

	memcpy(GPUPtr,IBuffer->getData(offset),size);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	return true;
}

bool GLManager::deleteBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<GLHandle*>(buffer->_handle.get());
	glDeleteBuffers(1,&handle->ID);
	return true;
}

bool GLManager::useVertexBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<GLHandle*>(buffer->_handle.get());

	glBindBuffer(GL_ARRAY_BUFFER,handle->ID);
	return true;
}

bool GLManager::useIndexBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<GLHandle*>(buffer->_handle.get());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,handle->ID);
	return true;
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
	return true;
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

bool GLManager::useShader(GPUResource* shader){
	auto handle = dynamic_cast<GLShaderHandle*>(shader->_handle.get());

	glUseProgram(handle->program);

	return true;
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

bool GLManager::updateUniformBuffer(GPUResource* buffer,unsigned int offset,unsigned int size){
	auto UBuffer = dynamic_cast<GXWrapper::UniformBuffer*>(buffer);


	auto handle = dynamic_cast<GLHandle*>(UBuffer->_handle.get());

	glBindBuffer(GL_UNIFORM_BUFFER,handle->ID);
	void* GPUPtr = NULL;
	GPUPtr = glMapBufferRange(GL_UNIFORM_BUFFER,offset,size,GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	if(GPUPtr == NULL)
		throw GXWrapper::GPUException("Cannot Map Index Buffer: Failed to get buffer pointer");

	memcpy(GPUPtr,UBuffer->getData(offset),size);
	glUnmapBuffer(GL_UNIFORM_BUFFER);

	glBindBuffer(GL_UNIFORM_BUFFER,0);
	return true;
}

bool GLManager::useUniformBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<GLHandle*>(buffer->_handle.get());
	glBindBuffer(GL_UNIFORM_BUFFER,handle->ID);
	return true;
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

bool GLManager::updateTexture2D(GPUResource* texture,Image& img){
	auto handle = dynamic_cast<GLHandle*>(texture->_handle.get());

	glBindTexture(GL_TEXTURE_2D,handle->ID);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getWidth(),img.getHeight(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.getPixels());
	glBindTexture(GL_TEXTURE_2D,0);
	return true;
}

bool GLManager::deleteTexture2D(GPUResource* texture){
	auto handle = dynamic_cast<GLHandle*>(texture->_handle.get());

	glDeleteTextures(1,&handle->ID);

	return true;
}

bool GLManager::useTexture2D(GPUResource* texture, unsigned int unit, Shader::Type)
{
	auto handle = dynamic_cast<GLHandle*>(texture->_handle.get());

	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D,handle->ID);

	return true;
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

bool GLManager::drawGeometry(Geometry* geometry, Primitive::Mode mode)
{
	auto geo = (geometry);

	auto handle = dynamic_cast<GLHandle*>(geo->_handle.get());

	glBindVertexArray(handle->ID);

	auto geoData = geo->_geometryData;
		
	geoData.primitive;

	switch (mode)
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

bool GLManager::deleteGeometry(GPUResource* geometry)
{
	auto handle = dynamic_cast<GLHandle*>(geometry->_handle.get());

	glDeleteVertexArrays(1,&handle->ID);

	return true;
}

bool GLManager::createSamplerState(GPUResource*)
{
	return true;
}

bool GLManager::useSamplerState(GPUResource*, unsigned slot, Shader::Type type)
{
	return true;
}

bool GLManager::deleteSamplerState(GPUResource*)
{
	return true;
}

bool GLManager::applySamplerStateToTexture2D(GPUResource* gpSampler, GPUResource* texture)
{
	auto texHandle = dynamic_cast<GLHandle*>(texture->_handle.get());
	auto tex = dynamic_cast<Texture*>(texture);
	auto sampler = dynamic_cast<SamplerState*>(gpSampler);


	if(tex->getType() == Texture::TEXTURE2D){
		glBindTexture(GL_TEXTURE_2D,texHandle->ID);
		applyFilter2D(sampler->filter,tex->usingMipMaps(),texHandle);
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