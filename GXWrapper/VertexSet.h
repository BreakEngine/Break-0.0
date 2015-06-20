#pragma once
#include "ISet.h"
#include "IVertex.h"
#include "VertexDeclaration.h"
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

			virtual Infrastructure::RAMBufferPtr getData() override{
				if(_data.size()>0){
					auto ret = std::make_shared<Infrastructure::RAMBuffer>(&_data[0],_data.size()*declaration.getSize());
					return ret;
				}else{
					return nullptr;
				}
			}

			//holds a declaration of the contained vertices
			VertexDeclaration declaration;
			
			VertexSet(VertexDeclaration _decelaration){
				declaration = _decelaration;
			}

			VertexSet(){

			}

			virtual ~VertexSet(){
				_data.clear();
			}

			virtual VertexDeclaration getDeclaration() override {
				return declaration;
			}

		};

	}

}