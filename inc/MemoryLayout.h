#pragma once

#include "MemoryElement.h"
#include <vector>
#include "GlobalDefinitions.h"

namespace Break{
	namespace GXWrapper{

		/**
		 * \brief represnets memory input layout
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX MemoryLayout{
		protected:
			///size of full data
			u32 _size;

			///calculates the size of the memory layout
			u32 calcSize();
		public:
			///elements vector
			std::vector<MemoryElement> elements;

			///default constructor
			MemoryLayout();
			///vector init constructor
			MemoryLayout(std::vector<MemoryElement>& e);
			///raw pointer init constructor
			MemoryLayout(MemoryElement* e, u32 count);
			///copy constrcutor
			MemoryLayout(const MemoryLayout& val);

			/**
			 * \brief appends element to layout
			 * \param v element to be appended
			 * \author Moustapha Saad
			 */
			void append(MemoryElement v);

			///size getter
			u32 getSize();

			///count getter
			u32 getElementCount();

			///equality check function
			bool equals(const MemoryLayout& val);

			///destrcutor
			~MemoryLayout();

		};
	}
}