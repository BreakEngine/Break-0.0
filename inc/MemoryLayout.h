#pragma once

#include "MemoryElement.h"
#include <vector>

namespace Break{
	namespace GXWrapper{
		class MemoryLayout{
		protected:
			//size of full data
			uint _size;

			uint calcSize();
		public:
			//elements vector
			std::vector<MemoryElement> elements;

			MemoryLayout();
			MemoryLayout(std::vector<MemoryElement>& e);
			MemoryLayout(MemoryElement* e, uint count);
			MemoryLayout(const MemoryLayout& val);

			void append(MemoryElement& v);

			uint getSize();

			uint getElementCount();

			~MemoryLayout();

		};
	}
}