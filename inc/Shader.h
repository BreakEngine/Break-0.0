#pragma once
#include "GPUResource.h"
#include "MemoryLayout.h"
#include <string>
#include <memory>
#include <map>
#include "SamplerState.h"
#include "IAsset.h"

namespace Break{
	namespace GXWrapper{
		class Texture;

		///represnets a row in uniform table
		struct uniformRow{
			std::string _blockName;
			unsigned int _offset,_size;
		};
		///represents a row in samplers table
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

		///represents a GPU program
		class Shader:public Infrastructure::GPUResource, public Assets::IAsset{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		protected:

			///invokes create function to GPU
			virtual bool createGPUResource() override;

			///will hold the uniform blocks id for assigning later
			std::map<std::string, std::shared_ptr<UniformBuffer> > _uniformBlocks;
			///holds uniform names
			std::map<std::string, uniformRow> _uniformsTable;
			///holds samplers of this shader
			std::map<std::string, samplersRow> _samplersTable;

			///shader actual program in GLSL or HLSL
			std::string _vs,_ps;
			///shader layout
			MemoryLayout _inputLayout;
		public:
			///shader type
			enum Type{ NONE=0, VERTEX=1, PIXEL=2};

			/**
			 * \brief init shader constructor
			 * \param vs vertex shader program
			 * \param ps pixel shader program
			 * \param layout shader input layout
			 * \author Moustapha Saad
			 */
			Shader(std::string vs, std::string ps,MemoryLayout inputLayout);
			Shader(const Shader&);
			virtual ~Shader();

			///binds this shader program to be used and updates uniform buffers
			void use();

			///sets uniform to uniform block
			void setUniform(std::string name,void* ptr);
			///binds texture to sampler unit
			void setTexture(std::string sampler,Texture* tex);

			/**
			 * \brief register uniform block in the shader
			 * \param name name of the uniform block
			 * \param size size of the uniform block
			 * \param slot uniform block index in the program
			 * \param shader type of the shader that this block in
			 * \author Moustapha Saad
			 */
			void registerUniformBlock(std::string name,unsigned int size, unsigned int slot,Shader::Type shader);

			/**
			 * \brief registers a uniform in uniform block
			 * \param name name of the uniform
			 * \param blockName name of the uniform block name
			 * \param offset offset of the unifrom inside block
			 * \param size size of the uniform inside the block
			 * \author Moustapha Saad
			 */
			void registerUniform(std::string name,std::string blockName,unsigned int offset, unsigned int size);

			/**
			 * \brief registers a sampler to this shader
			 * \param name name of the sampler
			 * \param slot index of this sampler in the shader
			 * \param state the actual state that will be registered
			 * \param shader type of the shader that this sampler in
			 * \author Moustapha Saad
			 */
			void registerSampler(std::string name,unsigned int slot, SamplerStatePtr state,Shader::Type shader);

			///flushes the uniform block data to GPU
			void flushUniforms();

			///gets vertex shader code
			std::string getVertexShader();
			///gets pixel shader code
			std::string getPixelShader();
			///gets vertex shader input layout
			MemoryLayout getInputLayout();
		};
		typedef std::shared_ptr<Shader> ShaderPtr;
	}
}