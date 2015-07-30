#include "Geometry.h"
#include <Engine.h>

using namespace Break::GXWrapper;

bool Geometry::createGPUResource()
{
	return Infrastructure::Engine::Instance->GraphicsDevice->createGeometry(this);
}

Geometry::Geometry(ISet* vertices, ISet* indices,Primitive::Type type){
	_geometryData.primitive = type;
	if(vertices){
		_declaration = vertices->getDeclaration();
		_geometryData.vertices = std::make_shared<VertexBuffer>(vertices,_declaration);
		_geometryData.verticesCount = vertices->count();
		_geometryData.verticesOffset = 0;
	}

	if(indices && indices->count()>0){
		_geometryData.indices = std::make_shared<IndexBuffer>(indices);
		_geometryData.indicesCount = indices->count();
		_geometryData.indicesOffset = 0;
	}
	createGPUResource();
}

Geometry::Geometry(const Geometry& val){
		_declaration = val._declaration;
		_geometryData = val._geometryData;
}

Geometry::~Geometry(){
	Break::Infrastructure::Engine::Instance->GraphicsDevice->deleteGeometry(this);
}

unsigned int* Geometry::getIndices(){
	unsigned int* head = reinterpret_cast<unsigned int*>(_geometryData.indices->getData(_geometryData.indicesOffset));
	return head;
}

unsigned int Geometry::getIndicesCount(){
	return _geometryData.indicesCount;
}

MemoryLayout Geometry::getMemoryLayout()
{
	return _declaration;
}

GeometryData Geometry::getGeometryData()
{
	return _geometryData;
}

void Geometry::draw(Primitive::Mode mode)
{
	Break::Infrastructure::Engine::Instance->GraphicsDevice->drawGeometry(this,mode);
}

unsigned int Geometry::getVerticesCount(){
	return _geometryData.verticesCount;
}