#pragma once
#include "ISet.h"
namespace Break{
	namespace GXWrapper{
		/*!
		 * special class of set that holds vertices
		 */
		class IndexSet : public Set<unsigned int>{
		public:
			virtual Infrastructure::RAMBufferPtr getData(bool shallow = false)override{
				if(_data.size()>0){
					unsigned int size = _data.size()*sizeof(unsigned int);
					auto res = std::make_shared<Infrastructure::RAMBuffer>(&_data[0],size,!shallow);
					return res;
				}else{
					return nullptr;
				}
			}
		};
	}
}