#pragma once
#include "GPUResource.h"
#include "MemoryLayout.h"
#include <string>
#include <memory>
#include <map>
#include "SamplerState.h"

namespace Break{
	namespace GXWrapper{
		class Texture;

		struct uniformRow{
			std::string _blockName;
			unsigned int _offset,_size;
		};
		struct samplersRow
		{
			unsigned int _slot;
			unsigned int _shader;
			std::shared_ptr<SamplerState> _state;

			samplersRow()
			{
				_state = nullptr;
			}

			~samplersRow()
			{
				_state = nullptr;
			}
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
			std::map<std::string, samplersRow> _samplersTable;

			std::string _vs,_ps;
			MemoryLayout _inputLayout;
		public:
			enum Type{ NONE=0, VERTEX=1, PIXEL=2};
			Shader(std::string vs, std::string ps,MemoryLayout& inputLayout);
			Shader(const Shader&);
			virtual ~Shader();

			void use();

			void setUniform(std::string name,void* ptr);
			void setTexture(std::string sampler,Texture* tex);

			void registerUniformBlock(std::string name,unsigned int size, unsigned int slot,Shader::Type shader);
			void registerUniform(std::string name,std::string blockName,unsigned int offset, unsigned int size);
			void registerSampler(std::string name,unsigned int slot, SamplerStatePtr state,Shader::Type shader);
			
			std::string getVertexShader();
			std::string getPixelShader();
			MemoryLayout getInputLayout();
		};
		typedef std::shared_ptr<Shader> ShaderPtr;
	}
}