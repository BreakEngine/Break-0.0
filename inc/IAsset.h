#pragma once
#include <string>
#include <memory>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Assets{
		class ResourceManager;
		/**
		 * \brief represents a Asset class
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX IAsset{
		friend class AssetManager;
		public:
			///type of the asset
			enum Type
			{
				UNDEFINED, IMAGE, SHADER
			};


			/**
			 * \brief defualt constructor
			 * \param name name of asset (OPTIONAL) default is empty string
			 * \param type type of the asset (OPTIONAL) default is UNDEFINED
			 * \author Moustapha Saad
			 */
			IAsset(std::string name="", Type type = Type::UNDEFINED):_name(name),_type(type){}

			/**
			 * \brief type getter
			 * \return Type of the asset
			 * \author Moustapha Saad
			 */
			Type getType(){
				return _type;
			}

			/**
			 * \brief name getter
			 * \return name of the asset
			 * \author Moustapha Saad
			 */
			std::string getName(){
				return _name;
			}

		protected:
			///type of the asset
			Type _type;
			///name of the asset
			std::string _name;
		};
		///type alias of the Asset shared_ptr
		typedef std::shared_ptr<IAsset> IAssetPtr;
	}
}