#pragma once

#include "MemoryElement.h"
#include <vector>

namespace Break{
	namespace GXWrapper{

		/**
		 * \brief represnets memory input layout
		 * \author Moustapha Saad
		 */
		class MemoryLayout{
		protected:
			///size of full data
			uint _size;

			///calculates the size of the memory layout
			uint calcSize();
		public:
			///elements vector
			std::vector<MemoryElement> elements;

			///default constructor
			MemoryLayout();
			///vector init constructor
			MemoryLayout(std::vector<MemoryElement>& e);
			///raw pointer init constructor
			MemoryLayout(MemoryElement* e, uint count);
			///copy constrcutor
			MemoryLayout(const MemoryLayout& val);

			/**
			 * \brief appends element to layout
			 * \param v element to be appended
			 * \author Moustapha Saad
			 */
			void append(MemoryElement v);

			///size getter
			uint getSize();

			///count getter
			uint getElementCount();

			///equality check function
			bool equals(const MemoryLayout& val);

			///destrcutor
			~MemoryLayout();

		};
	}
}