#pragma once
#include <string>
#include <memory>

namespace Break{
	namespace GXWrapper{
		class ResourceManager;
		class IResource{
		friend class ResourceManager;
		public:
			enum Type
			{
				UNDEFINED, IMAGE
			};


			IResource(std::string name="", Type type = Type::UNDEFINED):_name(name),_type(type){}

			Type getType(){
				return _type;
			}

			std::string getName(){
				return _name;
			}
		protected:
			Type _type;
			std::string _name;
		};
		typedef std::shared_ptr<IResource> IResourcePtr;
	}
}