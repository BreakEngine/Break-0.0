#define GLM_FORCE_RADIANS
#include "Shape2D.h"
#include <Shader.h>
#include <AssetManager.h>
#include <Engine.h>
using namespace std;
using namespace Break::GXWrapper;
using namespace Break::Assets;
using namespace Break::Graphics;

Shape2D::Shape2D():_vertices(Vertex2DPosColorTex::getDescription())
{
	_fillColor = glm::vec4(1,1,1,1);
	_texture = nullptr; 
	_needUpdate = false;
	_geometry = nullptr;
}

Shape2D::~Shape2D()
{
	_geometry = nullptr;
	_texture = nullptr;
}

void Shape2D::append(glm::vec2 v, glm::vec4 color, glm::vec2 tex)
{
	int count = _vertices.count();
	if(count>=3)
	{
		_indices.append(count-2);
		_indices.append(count-1);
		_indices.append(count);
	}else
	{
		_indices.append(count);
	}
	if(color == glm::vec4(-1,-1,-1,-1))
		_vertices.append(Vertex2DPosColorTex(v,_fillColor,tex));
	else
		_vertices.append(Vertex2DPosColorTex(v,color,tex));

	_needUpdate = true;

}

void Shape2D::append(float x, float y)
{
	append(glm::vec2(x,y),_fillColor);
}

void Shape2D::setTexture(std::shared_ptr<Texture> texture)
{
	_texture = texture;
}

Texture* Shape2D::getTexture()
{
	if(_texture)
		return _texture.get();
	else
		return NULL;
}

void Shape2D::setPosition(float x, float y)
{
	transform.position.x = x;
	transform.position.y = y;
}

void Shape2D::setScale(float x, float y)
{
	transform.scale.x = x;
	transform.scale.y = y;
}

void Shape2D::rotate(float angle)
{
	transform.rotate(glm::vec3(0,0,1),angle);
}

void Shape2D::setFillColor(Color color)
{
	_fillColor = color;
	for(int i=0;i<_vertices.count();i++)
	{
		_vertices[i].color = _fillColor;
	}
}

void Shape2D::draw()
{
	Shader* shader = static_cast<Shader*>(AssetManager::find("_shape2DShader"));
	if(_needUpdate)
	{
		_geometry = std::make_shared<Geometry>(_vertices,&_indices,Primitive::TRIANGLES);
		_needUpdate = false;
	}
	//shader->setUniform("model",&glm::mat4(1));
    auto tmat = transform.getMatrix();
    auto idmat = glm::mat4(1);
    auto proj = Infrastructure::Engine::Instance->get2DOrthogonal();
	shader->setUniform("model",&tmat);
	shader->setUniform("view",&idmat);
	shader->setUniform("projection",&proj);
	glm::vec4 hasTex = glm::vec4(0,1,1,1);
	if(_texture){
		hasTex.x=1;
		shader->setTexture("spTex",_texture.get());
	}
	shader->setUniform("hasTexture",&hasTex);
	//shader->setUniform("projection",&glm::mat4(1));
	shader->use();
	if(_geometry){
		Infrastructure::Engine::Instance->GraphicsDevice->setCullMode(Infrastructure::CullMode::NONE);
		_geometry->draw();
		Infrastructure::Engine::Instance->GraphicsDevice->setCullMode(Infrastructure::CullMode::BACK);
	}
}

