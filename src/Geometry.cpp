#include "Geometry.h"
#include "Engine.h"
#include <Services.h>

using namespace Break::GXWrapper;

bool Geometry::createGPUResource()
{
	//return Break::Infrastructure::Engine::Instance->GraphicsDevice->createGeometry(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::GEN;

	ins.args.push(Renderer::GPU_ISA::GEOMETRY);
	ins.args.push(_geometryData.vertices->getHandle());
	ins.args.push(_geometryData.indices->getHandle());
	MemoryLayout layout = _geometryData.vertices->getLayout();
	ins.args.push(&layout);
	_handle = Services::getGPU_VM()->execute(ins);
	return true;
}

Geometry::Geometry(ISet& vertices, ISet* indices,Primitive::Type type){
	_geometryData.primitive = type;
	
		_declaration = vertices.getDeclaration();
		_geometryData.vertices = std::make_shared<VertexBuffer>(&vertices,_declaration);
		_geometryData.verticesCount = vertices.count();
		_geometryData.verticesOffset = 0;

	if(indices && indices->count()>0){
		_geometryData.indices = std::make_shared<IndexBuffer>(indices);
		_geometryData.indicesCount = indices->count();
		_geometryData.indicesOffset = 0;
	}
	createGPUResource();
}

Geometry::Geometry(VertexBuffer* vb,MemoryLayout layout,IndexBuffer* ib,Primitive::Type type)
{
	_geometryData.primitive = type;
	
	_declaration = layout;
	if(vb) {
		_geometryData.vertices = std::shared_ptr<VertexBuffer>(vb);
		_geometryData.vertices->setLayout(layout);
		_geometryData.verticesCount = 0;
		_geometryData.verticesOffset = 0;
	}

	if(ib){
		_geometryData.indices = std::shared_ptr<IndexBuffer>(ib);
		_geometryData.indicesCount = 0;
		_geometryData.indicesOffset = 0;
	}
	createGPUResource();
}

Geometry::Geometry(const Geometry& val){
		_declaration = val._declaration;
		_geometryData = val._geometryData;
}

Geometry::~Geometry(){
	//Break::Infrastructure::Engine::Instance->GraphicsDevice->deleteGeometry(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::DEL;
	ins.args.push(Renderer::GPU_ISA::GEOMETRY);
	ins.args.push(_handle.get());

	Services::getGPU_VM()->execute(ins);
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

GeometryData& Geometry::getGeometryData()
{
	return _geometryData;
}

void Geometry::draw()
{
	if(_geometryData.vertices && _geometryData.indices){
		//Break::Infrastructure::Engine::Instance->GraphicsDevice->drawGeometry(this,Primitive::Mode::INDEXED);
		Renderer::GPUIns ins;
		ins.instruction = Renderer::GPU_ISA::DRAW_INDEXED;

		ins.args.push(_geometryData.primitive);
		ins.args.push(_handle.get());
		ins.args.push(_geometryData.vertices->getHandle());
		ins.args.push(_geometryData.indices->getHandle());
		ins.args.push(_geometryData.indicesCount);
		ins.args.push(&_declaration);

		Services::getGPU_VM()->execute(ins);
	}else if(_geometryData.vertices){
		//Break::Infrastructure::Engine::Instance->GraphicsDevice->drawGeometry(this,Primitive::Mode::NORMAL);
		Renderer::GPUIns ins;
		ins.instruction = Renderer::GPU_ISA::DRAW;

		ins.args.push(_geometryData.primitive);
		ins.args.push(_handle.get());
		ins.args.push(_geometryData.vertices->getHandle());
		ins.args.push(_geometryData.verticesCount);
		ins.args.push(&_declaration);

		Services::getGPU_VM()->execute(ins);
	}
}

unsigned int Geometry::getVerticesCount(){
	return _geometryData.verticesCount;
}