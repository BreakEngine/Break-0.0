#include "Geometry.h"

using namespace Break::GXWrapper;

Geometry::Geometry()
{

}

Geometry::Geometry(ISet* vertices, ISet* indices)
{

	if(vertices)
	{
		_declaration = vertices->getDeclaration();
		_handle.vertices = std::make_shared<VertexBuffer>(vertices,_declaration);
		_handle.verticesCount = vertices->count();
		_handle.verticesOffset = 0;
	}

	if(indices)
	{
		_handle.indices = std::make_shared<IndexBuffer>(indices);
		_handle.indicesCount = indices->count();
		_handle.indicesOffset = 0;
	}

}

Geometry::Geometry(const Geometry& val)
{
		_declaration = val._declaration;
		_handle = val._handle;
}

Geometry::~Geometry()
{

}

bool Geometry::createGPUResource()
{
	return false;
}

void Geometry::use()
{
}

unsigned int* Geometry::getIndices()
{
	unsigned int* head = reinterpret_cast<unsigned int*>(_handle.indices->getData(_handle.indicesOffset));
	return head;
}

unsigned int Geometry::getIndicesCount()
{
	return _handle.indicesCount;
}

unsigned int Geometry::getVerticesCount()
{
	return _handle.verticesCount;
}


void Geometry::Draw(Primative::Type _primative , Primative::Mode _mode)
{
	Break::Infrastructure::Engine::Instance->GraphicsDevice->Draw(this,_primative,_mode);
}

void Geometry::setInstance_Count(int _count)
{
	_handle.Instance_Count = _count;
}