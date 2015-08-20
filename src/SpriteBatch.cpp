#define GLM_FORCE_RADIANS
#include "SpriteBatch.h"
#include "AssetManager.h"
#include <memory>
#include "Engine.h"
#include <glm/gtc/matrix_transform.hpp>
#include <Sprite.h>
#include "MathUtils.h"
using namespace Break::Infrastructure;
using namespace Break::Graphics;
using namespace Break::GXWrapper;
using namespace std;

void SpriteBatch::checkFlush(Texture2D* texture)
{
	if(texture!=_texture)
	{
		flush();
	}
	_texture = texture;
}

glm::vec2 SpriteBatch::rotatePoint(glm::vec2 point, float angle)
{
	auto mat = glm::rotate(glm::mat4(1),MathUtils::toRadians(angle),glm::vec3(0,0,1));
	auto result = mat*glm::vec4(point.x,point.y,0,1);
	return glm::vec2(result.x,result.y);
}

SpriteBatch::SpriteBatch(ShaderPtr shader):_vertices(Assets::Vertex2DPosColorTex::getDescription())
{
	_vertices.resize(2000*4);
	_indices.resize(2000*6);
	if(shader)
	{
		_shader = shader.get();
		_customShader = true;
	}else{
		_shader = static_cast<Shader*>(Assets::AssetManager::find("_shape2DShader"));
		_customShader = false;
	}
	/*
	_geometry = std::make_shared<Geometry>(*new VertexBuffer(256000, VertexBuffer::DYNAMIC),Assets::Vertex2DPosColorTex::getDescription(),
		new IndexBuffer(48000,IndexBuffer::DYNAMIC),Primitive::TRIANGLES);
	*/
	auto vbuffer = make_shared<Infrastructure::RAMBuffer>(&_vertices[0],256000,false);
	_geometry = std::make_shared<Geometry>(new VertexBuffer(vbuffer,
		Assets::Vertex2DPosColorTex::getDescription(), VertexBuffer::DYNAMIC),
		Assets::Vertex2DPosColorTex::getDescription(),
		new IndexBuffer(make_shared<Infrastructure::RAMBuffer>(&_indices[0],48000,false),IndexBuffer::DYNAMIC),Primitive::TRIANGLES);

	_count = 0;
	iCount = 0;
	vCount = 0;
}

SpriteBatch::~SpriteBatch()
{
	_geometry = nullptr;
	if(_customShader)
		delete _shader;
}

std::shared_ptr<Sprite> SpriteBatch::newSprite(Texture2DPtr tex)
{
	std::shared_ptr<Sprite> res=nullptr;
	if(tex)
	{
		res= make_shared<Sprite>(this,tex);
	}else
	{
		res= make_shared<Sprite>(this);
	}
	return res;
}

void SpriteBatch::begin()
{
	iCount=0;
	vCount=0;
	_count=0;

    auto idmat = glm::mat4(1);
    auto proj = Infrastructure::Engine::Instance->get2DOrthogonal();

	_shader->setUniform("model",&idmat);
	_shader->setUniform("view",&idmat);
	_shader->setUniform("projection",&proj);
	_shader->use();
}

void SpriteBatch::draw(Texture2D* texture, int x, int y, Color color)
{
	draw(texture,Rect(x,y,texture->getWidth(),texture->getHeight()),0,color);
}

void SpriteBatch::draw(Texture2D* texture, int x, int y, int width, int height, Color color)
{
	draw(texture,Rect(x,y,width,height),Rect(0,0,1,1),0,color);
}

void SpriteBatch::draw(Texture2D* texture, Rect dest, float angle, Color color)
{
	if(texture)
		draw(texture,dest,Rect(0,0,texture->getWidth(),texture->getHeight()),angle,color);
	else
		draw(texture,dest,Rect(0,0,1,1),angle,color);
}

void SpriteBatch::draw(Texture2D* texture, Rect dest, Rect src, float angle, Color color)
{
	checkFlush(texture);

	if(_count>=_limit)
		flush();

	auto p1 = rotatePoint(glm::vec2(0,0),angle)+glm::vec2(dest.x,dest.y);
	auto p2 = rotatePoint(glm::vec2(0,dest.height),angle)+glm::vec2(dest.x,dest.y);
	auto p3 = rotatePoint(glm::vec2(dest.width,0),angle)+glm::vec2(dest.x,dest.y);
	auto p4 = rotatePoint(glm::vec2(dest.width,dest.height),angle)+glm::vec2(dest.x,dest.y);

	glm::vec2 t1,t2,t3,t4;
	if(texture){
		t1 = glm::vec2(src.x/texture->getWidth(),src.y/texture->getHeight());
		t2 = glm::vec2(src.x/texture->getWidth(),(src.y+src.height)/texture->getHeight());
		t3 = glm::vec2((src.x+src.width)/texture->getWidth(),src.y/texture->getHeight());
		t4 = glm::vec2((src.x+src.width)/texture->getWidth(),(src.y+src.height)/texture->getHeight());
	}else
	{
		t1 = glm::vec2(0,0);
		t2 = glm::vec2(0,1);
		t3 = glm::vec2(1,0);
		t4 = glm::vec2(1,1);
	}

	_vertices[vCount] = Assets::Vertex2DPosColorTex(p1,color,t1);
	_vertices[vCount+1] = Assets::Vertex2DPosColorTex(p2,color,t2);
	_vertices[vCount+2] = Assets::Vertex2DPosColorTex(p3,color,t3);
	_vertices[vCount+3] = Assets::Vertex2DPosColorTex(p4,color,t4);

	_indices[iCount] = vCount+0;
	_indices[iCount+1] = vCount+1;
	_indices[iCount+2] = vCount+2;
	_indices[iCount+3] = vCount+2;
	_indices[iCount+4] = vCount+1;
	_indices[iCount+5] = vCount+3;
	
	vCount+=4;
	iCount+=6;
	_count++;
}

void SpriteBatch::flush()
{
	if(_count<=0)
		return;

	if(_texture){
		_shader->setTexture("spTex",_texture);
		glm::vec4 hasTex = glm::vec4(1,1,1,1);
		_shader->setUniform("hasTexture",&hasTex);
		_shader->use();
	}else
	{
		glm::vec4 hasTex = glm::vec4(0,1,1,1);
		_shader->setUniform("hasTexture",&hasTex);
		_shader->use();
	}

	//_geometry->getGeometryData().vertices->fromHandle(&_vertices[0],_vertices.count()*_vertices.declaration.getSize());
	//_geometry->getGeometryData().indices->fromHandle(&_indices[0],_indices.count()*4);
	_geometry->getGeometryData().vertices->flush();
	_geometry->getGeometryData().indices->flush();
	_geometry->getGeometryData().indicesCount = iCount;
	_geometry->getGeometryData().verticesCount = vCount;
	_geometry->draw();
	//_geometry->getGeometryData().vertices->clear();
	//_geometry->getGeometryData().indices->clear();
	_geometry->getGeometryData().indicesCount = 0;
	_geometry->getGeometryData().verticesCount = 0;
	//_vertices.clear();
	//_indices.clear();

	_count = 0;
	vCount = 0;
	iCount = 0;
}

void SpriteBatch::end()
{
	if(_count>0)
		flush();
}