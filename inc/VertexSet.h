#pragma once
#include "ISet.h"
#include "IVertex.h"
#include "MemoryLayout.h"
#include <memory>
#include <exception>

namespace Break{

	namespace GXWrapper{

		/*!
		 * special class of set that holds vertices
		 */
		template<typename T>
		class VertexSet : public Set<T>{
		public:

			/**
			 * \brief returns a raw ram buffer of the current data
			 * \param shallow indicates wether data will be copied deep or shallow (OPTIONAL, default is deep)
			 * \return a shared_ptr to ram buffer
			 * \author Moustapha Saad
			 */
			virtual Infrastructure::RAMBufferPtr getData(bool shallow = false) override{
				if(this->_data.size()>0){
					auto ret = std::make_shared<Infrastructure::RAMBuffer>(&this->_data[0],this->_data.size()*declaration.getSize(),!shallow);
					return ret;
				}else{
					return nullptr;
				}
			}

			//holds a declaration of the contained vertices
			MemoryLayout declaration;
			
			VertexSet(MemoryLayout _decelaration){
				declaration = _decelaration;
			}

			VertexSet(){

			}

			virtual ~VertexSet(){
				this->_data.clear();
			}

			virtual MemoryLayout getDeclaration() override {
				return declaration;
			}

		};

	}

}