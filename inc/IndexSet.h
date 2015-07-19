#pragma once
#include "ISet.h"
namespace Break{
	namespace GXWrapper{
		/*!
		 * special class of set that holds vertices
		 */
		class IndexSet : public Set<unsigned int>{
		public:
			virtual Infrastructure::RAMBufferPtr getData(){
				if(_data.size()>0){
					unsigned int size = _data.size()*sizeof(unsigned int);
					auto res = std::make_shared<Infrastructure::RAMBuffer>(&_data[0],size);
					return res;
				}else{
					return nullptr;
				}
			}

			virtual void mirror() override
			{
				std::vector<unsigned int> res;
				unsigned int size = _data.size();
				res.resize(size);
				for(int i=0;i<size;i++)
					res.push_back(_data[size-i-1]);

				_data = res;
			}
		};
	}
}