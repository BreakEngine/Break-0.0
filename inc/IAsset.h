#pragma once
#include <string>
#include <memory>

namespace Break{
	namespace Assets{
		class ResourceManager;
		class IAsset{
		friend class AssetManager;
		public:
			enum Type
			{
				UNDEFINED, IMAGE, SHADER
			};


			IAsset(std::string name="", Type type = Type::UNDEFINED):_name(name),_type(type){}

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
		typedef std::shared_ptr<IAsset> IAssetPtr;
	}
}