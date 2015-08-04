#pragma once
#include <vector>
#include "RAMBuffer.h"
#include "MemoryLayout.h"
namespace Break{
	namespace GXWrapper{
		/*!
		 * This class is meant to hold a set of data of any type, like vertices of indices
		 */

		class ISet{
		public:
			virtual Infrastructure::RAMBufferPtr getData(bool shallow = false)=0;

			virtual unsigned int count()=0;

			virtual MemoryLayout getDeclaration()=0;

			virtual void clear()=0;

			virtual ~ISet(){

			}
		};
		typedef std::shared_ptr<ISet> ISetPtr;
		
		template<class T>
		class Set : public ISet{
		protected:
			std::vector<T> _data;

		public:
			Set(){

			}

			virtual ~Set(){
				_data.clear();
			}

			virtual Infrastructure::RAMBufferPtr getData(bool shallow = false) override {
				return nullptr;
			}

			unsigned int count() override {
				return _data.size();
			}
			void clear()override{
				_data.clear();
			}

			void resize(unsigned int size)
			{
				_data.resize(size);
			}

			T& operator[](unsigned int ix) {
				return _data[ix];
			}

			virtual MemoryLayout getDeclaration() override {
				return MemoryLayout();
			}
		
			void append(T v){
				_data.push_back(v);
			}

			void erase(unsigned int startIX, unsigned int endIX){
				auto base = _data.begin();
				_data.erase(base+startIX,base+endIX+1);
			}

		};
	}
}