#pragma once
#include "ISet.h"
#include "GlobalDefinitions.h"
namespace Break{
	namespace GXWrapper{
		/*!
		 * \brief special class of set that holds indices
		 */
		class BREAK_API_EX IndexSet : public Set<unsigned int>{
		public:

			/**
			 * \brief returns a raw ram buffer of the current data
			 * \param shallow indicates wether data will be copied deep or shallow (OPTIONAL, default is deep)
			 * \return a shared_ptr to ram buffer
			 * \author Moustapha Saad
			 */
			virtual Infrastructure::RAMBufferPtr getData(bool shallow = false)override{
				if(_data.size()>0){
					unsigned int size = _data.size()*sizeof(unsigned int);

					auto res = std::make_shared<Infrastructure::RAMBuffer>();
					if(shallow)
						res->copyHandle(&_data[0],size);
					else
						res->copyBuffer(&_data[0],size);

					return res;
				}else{
					return nullptr;
				}
			}
		};
	}
}