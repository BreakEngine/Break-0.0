#include <iostream>
#include <cassert>
#include "GPU_VM.hpp"
#include "GPUException.h"
#include "VertexBuffer.h"
#include <Services.h>
using namespace Break;
using namespace std;
using namespace Break::Renderer;
using namespace Break::GXWrapper;

Arg GPU_VM::pop(std::queue<Arg>& args)
{
	if(args.size()<=0)
		throw GPUException("stack is out of arguments");

	Arg arg = args.front();

	args.pop();
	return arg;
}

GPU_VM::GPU_VM()
{
	//nothing to do here
}

GPU_VM::~GPU_VM()
{
	//nothing to do here
}

Infrastructure::IGPUHandlePtr GPU_VM::execute(GPUIns& ins)
{
	if(ins.instruction == GPU_ISA::GEN)
	{

		GPU_ISA tag_01 = pop(ins.args);
		if(tag_01 == GPU_ISA::VERTEX_BUFFER){
			GPU_ISA type = pop(ins.args);
			u32 size = pop(ins.args);
			void* data = pop(ins.args);

			auto res = Services::getGraphicsManager()->vm_createVertexBuffer(type,size,data);
			if(res == nullptr)
			{
				throw GPUException("Graphics Device failed to generate a Vertex Buffer");
			}else
			{
				return res;
			}
		}else if(tag_01 == GPU_ISA::INDEX_BUFFER)
		{
			GPU_ISA type = pop(ins.args);
			u32 size = pop(ins.args);
			void* data = pop(ins.args);

			auto res = Services::getGraphicsManager()->vm_createIndexBuffer(type,size,data);
			if(res == nullptr)
			{
				throw GPUException("Graphics Device failed to generate a Index Buffer");
			}else
			{
				return res;
			}
		}else if(tag_01 == GPU_ISA::UNIFORM_BUFFER)
		{
			u32 size = pop(ins.args);
			void* data = pop(ins.args);
			u32 slot = pop(ins.args);

			auto res = Services::getGraphicsManager()->vm_createUniformBuffer(size,data,slot);
			if(res == nullptr)
			{
				throw GPUException("Graphics Device failed to generate a Uniform Buffer");
			}else
			{
				return res;
			}
		}else if(tag_01 == GPU_ISA::PROGRAM)
		{
			std::string* vertex = pop(ins.args);
			std::string* pixel = pop(ins.args);
			MemoryLayout* input_layout = pop(ins.args);

			auto res = Services::getGraphicsManager()->vm_createProgram(*vertex,*pixel,input_layout);
			return res;
		}else if(tag_01 == GPU_ISA::TEXTURE2D)
		{
			GXWrapper::Image* img = pop(ins.args);
			bool mipmaps = pop(ins.args);

			auto res = Services::getGraphicsManager()->vm_createTexture2D(*img,mipmaps);
			return res;

		}else if(tag_01 == GPU_ISA::GEOMETRY)
		{
			Infrastructure::IGPUHandle* vertex = pop(ins.args);
			Infrastructure::IGPUHandle* index = pop(ins.args);
			MemoryLayout* input = pop(ins.args);

			auto res = Services::getGraphicsManager()->vm_createGeometry(vertex,index,input);
			return res;
		}else if(tag_01 == GPU_ISA::SAMPLER)
		{
			TextureAddressMode V,U,W;
			U = pop(ins.args);
			V = pop(ins.args);
			W = pop(ins.args);

			TextureFilter filter = pop(ins.args);

			CompareFunction func = pop(ins.args);

			Color* color = pop(ins.args);

			auto res = Services::getGraphicsManager()->vm_createSampleState(U,V,W,filter,func,color);
			return res;
		}else
		{
			throw GPUException("unifentified argument for gen instruction");
		}

	}else if(ins.instruction == GPU_ISA::MAP)
	{

		GPU_ISA tag_01 = pop(ins.args);
		if(tag_01 == GPU_ISA::VERTEX_BUFFER)
		{

			Infrastructure::IGPUHandle* handle = pop(ins.args);
			u32 size = pop(ins.args);
			void* data = pop(ins.args);

			Services::getGraphicsManager()->vm_mapVertexBuffer(handle,size,data);
			//auto res = std::shared_ptr<Infrastructure::IGPUHandle>(handle);
			return nullptr;

		}else if(tag_01 == GPU_ISA::INDEX_BUFFER)
		{

			Infrastructure::IGPUHandle* handle = pop(ins.args);
			u32 size = pop(ins.args);
			void* data = pop(ins.args);

			Services::getGraphicsManager()->vm_mapIndexBuffer(handle,size,data);
			//auto res = std::shared_ptr<Infrastructure::IGPUHandle>(handle);
			return nullptr;

		}else if(tag_01 == GPU_ISA::UNIFORM_BUFFER)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args);
			u32 size = pop(ins.args);
			void* data = pop(ins.args);

			Services::getGraphicsManager()->vm_mapUniformBuffer(handle,size,data);
			//auto res = std::shared_ptr<Infrastructure::IGPUHandle>(handle);
			return nullptr;
		}else if(tag_01 == GPU_ISA::TEXTURE2D)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args);
			Image* img = pop(ins.args);

			Services::getGraphicsManager()->vm_mapTexture2D(handle,*img);
			return nullptr;
		}else
		{
			throw GPUException("unifentified argument for map instruction");
		}

	}else if(ins.instruction == GPU_ISA::DEL)
	{
		
		GPU_ISA tag_01 = pop(ins.args);
		if(tag_01 == GPU_ISA::VERTEX_BUFFER)
		{

			Infrastructure::IGPUHandle* handle = pop(ins.args);

			Services::getGraphicsManager()->vm_deleteBuffer(handle);
			//auto res = std::shared_ptr<Infrastructure::IGPUHandle>(handle);
			return nullptr;

		}else if(tag_01 == GPU_ISA::INDEX_BUFFER)
		{

			Infrastructure::IGPUHandle* handle = pop(ins.args);

			Services::getGraphicsManager()->vm_deleteBuffer(handle);
			//auto res = std::shared_ptr<Infrastructure::IGPUHandle>(handle);
			return nullptr;

		}else if(tag_01 == GPU_ISA::UNIFORM_BUFFER)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args);

			Services::getGraphicsManager()->vm_deleteBuffer(handle);
			return nullptr;
		}else if(tag_01 == GPU_ISA::PROGRAM)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args);
			Services::getGraphicsManager()->vm_deleteShader(handle);
			return nullptr;
		}else if(tag_01 == GPU_ISA::TEXTURE2D)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args);
			Services::getGraphicsManager()->vm_deleteTexture2D(handle);
			return nullptr;
		}else if(tag_01 == GPU_ISA::GEOMETRY)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args);
			Services::getGraphicsManager()->vm_deleteGeometry(handle);
			return nullptr;
		}else if(tag_01 == GPU_ISA::SAMPLER)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args);
			Services::getGraphicsManager()->vm_deleteSampler(handle);
			return nullptr;
		}else
		{
			throw GPUException("unifentified argument for map instruction");
		}

	}else if(ins.instruction == GPU_ISA::BIND)
	{
		GPU_ISA tag_01 = pop(ins.args);
		if(tag_01 == GPU_ISA::VERTEX_BUFFER)
		{

			Infrastructure::IGPUHandle* handle = pop(ins.args);
			u32 stride = pop(ins.args);

			Services::getGraphicsManager()->vm_bindVertexBuffer(handle,stride);
			//auto res = std::shared_ptr<Infrastructure::IGPUHandle>(handle);
			return nullptr;

		}else if(tag_01 == GPU_ISA::INDEX_BUFFER)
		{

			Infrastructure::IGPUHandle* handle = pop(ins.args);

			Services::getGraphicsManager()->vm_bindIndexBuffer(handle);
			//auto res = std::shared_ptr<Infrastructure::IGPUHandle>(handle);
			return nullptr;

		}else if(tag_01 == GPU_ISA::UNIFORM_BUFFER)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args);
			GPU_ISA type = pop(ins.args);
			u32 slot = pop(ins.args);

			Services::getGraphicsManager()->vm_bindUniformBuffer(handle,type,slot);
			return nullptr;
		}else if(tag_01 == GPU_ISA::PROGRAM)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args); 

			Services::getGraphicsManager()->vm_bindShader(handle);
			return nullptr;
		}else if(tag_01 == GPU_ISA::TEXTURE2D)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args);
			GPU_ISA type = pop(ins.args);
			u32 unit = pop(ins.args);

			Services::getGraphicsManager()->vm_bindTexture2D(handle,type,unit);
			return nullptr;
		}else if(tag_01 == GPU_ISA::SAMPLER)
		{
			Infrastructure::IGPUHandle* handle = pop(ins.args); 
			GPU_ISA type = pop(ins.args);
			u32 slot = pop(ins.args);

			Services::getGraphicsManager()->vm_bindSampler(handle,type,slot);
			return nullptr;
		}else
		{
			throw GPUException("unifentified argument for map instruction");
		}
	}else if(ins.instruction == GPU_ISA::DRAW)
	{
		Primitive::Type type = pop(ins.args);
		Infrastructure::IGPUHandle* g_handle = pop(ins.args);
		Infrastructure::IGPUHandle* vertex = pop(ins.args);
		u32 vertices_count = pop(ins.args);
		MemoryLayout* input = pop(ins.args);

		Services::getGraphicsManager()->vm_draw(type,g_handle,vertex,
			vertices_count,input);
		return nullptr;
	}else if(ins.instruction == GPU_ISA::DRAW_INDEXED)
	{
		Primitive::Type type = pop(ins.args);
		Infrastructure::IGPUHandle* g_handle = pop(ins.args);
		Infrastructure::IGPUHandle* vertex = pop(ins.args);
		Infrastructure::IGPUHandle* index = pop(ins.args);
		u32 indices_count = pop(ins.args);
		MemoryLayout* input = pop(ins.args);

		Services::getGraphicsManager()->vm_drawIndexed(type,g_handle,
			vertex,index,indices_count,input);
		return nullptr;
	}else if(ins.instruction == GPU_ISA::APPLY)
	{
		GPU_ISA tag_01 = pop(ins.args);
		if(tag_01 == GPU_ISA::SAMPLER)
		{
			GPU_ISA tag_02 = pop(ins.args);
			if(tag_02 == GPU_ISA::TEXTURE2D)
			{
				Infrastructure::IGPUHandle* sampler = pop(ins.args);
				Infrastructure::IGPUHandle* texture = pop(ins.args);
				bool mipmaps = pop(ins.args);
				TextureAddressMode U = pop(ins.args);
				TextureAddressMode V = pop(ins.args);
				TextureFilter filter = pop(ins.args);
				CompareFunction func = pop(ins.args);
				Color* border_color = pop(ins.args);

				Services::getGraphicsManager()->vm_applySamplerTexture2D(sampler,
					texture,mipmaps,U,V,filter,func,*border_color);
				return nullptr;
			}else
			{
				throw GPUException("unidentfied APPLY SAMPLER instruction tag");
			}

		}else
		{
			throw GPUException("unidentfied APPLY instruction tag");
		}
	}else
	{
		throw GPUException("unidentfied instruction");
		return nullptr;
	}
}