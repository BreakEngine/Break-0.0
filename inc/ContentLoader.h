#pragma once
#include "IAsset.h"

namespace Break{
	namespace GXWrapper{
		class ContentLoader{
		public:
			template<class T>
			static std::shared_ptr<T> load(std::string file);
		};
	}
}