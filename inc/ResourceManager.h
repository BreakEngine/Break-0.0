#pragma once
#include <map>
#include "IResource.h"

namespace Break{
	namespace GXWrapper{
		class ResourceManager{
			static std::map<std::string,IResourcePtr> _resources;
		public:

			static IResourcePtr find(std::string);
			static void add(IResource*);
			static void add(std::string name,IResource* res);

			template<class T>
			static std::shared_ptr<T> load(std::string file);
		};
	}
}