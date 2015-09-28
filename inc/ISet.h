#pragma once
#include <vector>
#include "RAMBuffer.h"
#include "MemoryLayout.h"
#include "GlobalDefinitions.h"

namespace Break{
	namespace GXWrapper{

		/*!
		 * \brief This class is meant to hold a set of data of any type, like vertices of indices
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX ISet{
		public:
			/**
			 * \brief returns a raw ram buffer of the current data
			 * \param shallow indicates wether data will be copied deep or shallow (OPTIONAL, default is deep)
			 * \return a shared_ptr to ram buffer
			 * \author Moustapha Saad
			 */
			virtual Infrastructure::RAMBufferPtr getData(bool shallow = false)=0;

			/**
			 * \brief returns a data objects count
			 * \author Moustapha Saad
			 */
			virtual unsigned int count()=0;

			/**
			 * \brief returns a memory layout to data
			 * \author Moustapha Saad
			 */
			virtual MemoryLayout getDeclaration()=0;

			/**
			 * \brief clears data of the set
			 */
			virtual void clear()=0;

			///virtual destructor
			virtual ~ISet(){

			}
		};
		typedef std::shared_ptr<ISet> ISetPtr;
		
		template<class T>
		class BREAK_API_EX Set : public ISet{
		protected:
			///data list
			std::vector<T> _data;

		public:
			///default constructor
			Set(){

			}

			///default destrcutor
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

			/**
			 * \brief resizes the current list of the data
			 * \param size size to be resized to
			 * \author Moustapha Saad
			 */
			void resize(unsigned int size)
			{
				_data.resize(size);
			}

			/**
			 * \brief subscript operator to access data elements
			 * \param ix index of the element
			 * \return object reference to element
			 * \author Moustapha Saad
			 */
			T& operator[](unsigned int ix) {
				return _data[ix];
			}

			virtual MemoryLayout getDeclaration() override {
				return MemoryLayout();
			}

			/**
			 * \brief appends element object to data list
			 * \param v element object to be appended
			 * \author Moustapha Saad
			 */
			void append(T v){
				_data.push_back(v);
			}

			/**
			 * \brief erases a range of elements [inclusive]
			 * \param startIX start index of the range to be removed
			 * \param endIX end index of the range to be removed
			 * \author Moustapha Saad
			 */
			void erase(unsigned int startIX, unsigned int endIX){
				auto base = _data.begin();
				_data.erase(base+startIX,base+endIX+1);
			}

		};
	}
}