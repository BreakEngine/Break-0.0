#include "SpriteBatch.h"
#include "AssetManager.h"
#include <memory>
#include "Engine.h"
#include <glm\gtc\matrix_transform.hpp>
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
	auto mat = glm::rotate(glm::mat4(1),angle,glm::vec3(0,0,1));
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
	_geometry = std::make_shared<Geometry>(*new VertexBuffer(256000, VertexBuffer::DYNAMIC),Assets::Vertex2DPosColorTex::getDescription(),
		new IndexBuffer(48000,IndexBuffer::DYNAMIC),Primitive::TRIANGLES);

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

void SpriteBatch::begin()
{
	iCount=0;
	vCount=0;
	_count=0;

	_shader->setUniform("model",&glm::mat4(1));
	_shader->setUniform("view",&glm::mat4(1));
	_shader->setUniform("projection",&Infrastructure::Engine::Instance->get2DOrthogonal());
	_shader->use();
}

void SpriteBatch::draw(Texture2D* texture, int x, int y, Color color)
{
	draw(texture,Rect(x,y,texture->getWidth(),texture->getHeight()),0,color);
}

void SpriteBatch::draw(Texture2D* texture, int x, int y, int width, int height, Color color)
{
	draw(texture,Rect(x,y,width,height),0,color);
}

void SpriteBatch::draw(Texture2D* texture, Rect dest, float angle, Color color)
{
	checkFlush(texture);

	if(_count>=_limit)
		flush();

	auto p1 = rotatePoint(glm::vec2(0,0),angle)+glm::vec2(dest.x,dest.y);
	auto p2 = rotatePoint(glm::vec2(0,dest.height),angle)+glm::vec2(dest.x,dest.y);
	auto p3 = rotatePoint(glm::vec2(dest.width,0),angle)+glm::vec2(dest.x,dest.y);
	auto p4 = rotatePoint(glm::vec2(dest.width,dest.height),angle)+glm::vec2(dest.x,dest.y);
	/*
	_vertices.append(Assets::Vertex2DPosColorTex(p1,color,glm::vec2(0,0)));
	_vertices.append(Assets::Vertex2DPosColorTex(p2,color,glm::vec2(0,0)));
	_vertices.append(Assets::Vertex2DPosColorTex(p3,color,glm::vec2(0,0)));
	_vertices.append(Assets::Vertex2DPosColorTex(p4,color,glm::vec2(0,0)));

	_indices.append(vCount+0);
	_indices.append(vCount+1);
	_indices.append(vCount+2);
	_indices.append(vCount+2);
	_indices.append(vCount+1);
	_indices.append(vCount+3);
	*/
	_vertices[vCount] = Assets::Vertex2DPosColorTex(p1,color,glm::vec2(0,0));
	_vertices[vCount+1] = Assets::Vertex2DPosColorTex(p2,color,glm::vec2(0,1));
	_vertices[vCount+2] = Assets::Vertex2DPosColorTex(p3,color,glm::vec2(1,0));
	_vertices[vCount+3] = Assets::Vertex2DPosColorTex(p4,color,glm::vec2(1,1));

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

	_geometry->getGeometryData().vertices->fromHandle(&_vertices[0],_vertices.count()*_vertices.declaration.getSize());
	_geometry->getGeometryData().indices->fromHandle(&_indices[0],_indices.count()*4);
	_geometry->getGeometryData().vertices->flush();
	_geometry->getGeometryData().indices->flush();
	_geometry->getGeometryData().indicesCount = iCount;
	_geometry->getGeometryData().verticesCount = vCount;
	_geometry->draw(Primitive::Mode::INDEXED);
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