#include "Shape2D.h"
#include <Shader.h>
#include <AssetManager.h>
#include <Engine.h>
using namespace std;
using namespace Break::GXWrapper;
using namespace Break::Assets;

Break::Renderer::Shape2D::Shape2D():_vertices(Vertex2DPos::getDescription())
{
	_geometry = nullptr;
	_fillColor = glm::vec4(1,1,1,1);
	_needUpdate = false;
}

Break::Renderer::Shape2D::~Shape2D()
{
	_geometry = nullptr;

}

void Break::Renderer::Shape2D::append(glm::vec2 v)
{
	int count = _vertices.count();
	if(count>=3)
	{
		auto v1 = _vertices[count-2];
		auto v2 = _vertices[count-1];
		_vertices.append(v1);
		_vertices.append(v2);
	}
	_vertices.append(Vertex2DPos(v));
	_needUpdate = true;
}

void Break::Renderer::Shape2D::append(float x, float y)
{
	int count = _vertices.count();
	auto v = glm::vec2(x,y);
	if(count>=3)
	{
		auto v1 = _vertices[count-2];
		auto v2 = _vertices[count-1];
		_vertices.append(v1);
		_vertices.append(v2);
	}
	_vertices.append(Vertex2DPos(v));
	_needUpdate = true;
}

void Break::Renderer::Shape2D::setFillColor(GXWrapper::Color color)
{
	_fillColor = color;
}

void Break::Renderer::Shape2D::draw(GXWrapper::Primitive::Mode mode)
{
	Shader* shader = static_cast<Shader*>(AssetManager::find("_shape2DShader").get());
	if(_needUpdate)
	{
		_geometry = std::make_shared<Geometry>(&_vertices,nullptr,Primitive::TRIANGLES);
		_needUpdate = false;
	}
	shader->setUniform("ucolor",&_fillColor);
	shader->use();
	if(_geometry){
		Infrastructure::Engine::Instance->GraphicsDevice->setCullMode(Infrastructure::CullMode::NONE);
		_geometry->draw(Primitive::NORMAL);
		Infrastructure::Engine::Instance->GraphicsDevice->setCullMode(Infrastructure::CullMode::BACK);
	}
}

