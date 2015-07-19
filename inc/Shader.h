#pragma once
#include "GPUResource.h"
#include "MemoryLayout.h"
#include <string>
#include <memory>
#include <map>

namespace Break{
	namespace GXWrapper{
		struct uniformRow{
			std::string _blockName;
			unsigned int _offset,_size;
		};
		class UniformBuffer;
		class Shader:public Infrastructure::GPUResource{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		protected:

			virtual bool createGPUResource() override;

			//will hold the uniform blocks id for assigning later
			std::map<std::string, std::shared_ptr<UniformBuffer> > _uniformBlocks;
			std::map<std::string, uniformRow> _uniformsTable;

			std::string _vs,_ps;
			MemoryLayout _inputLayout;
		public:
			enum Type{ NONE=0, VERTEX=1, PIXEL=2};
			Shader(std::string vs, std::string ps,MemoryLayout& inputLayout);
			Shader(const Shader&);
			virtual ~Shader();

			void use();

			void setUniform(std::string name,void* ptr);

			void registerUniformBlock(std::string name,unsigned int size, unsigned int slot,Shader::Type shader);
			void registerUniform(std::string name,std::string blockName,unsigned int offset, unsigned int size);
			
			std::string getVertexShader();
			std::string getPixelShader();
			MemoryLayout getInputLayout();
		};
		typedef std::shared_ptr<Shader> ShaderPtr;
	}
}