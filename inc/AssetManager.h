#pragma once
#include <map>
#include "IAsset.h"
#include "GlobalDefinitions.h"

namespace Break
{
	namespace Infrastructure
	{
		class Engine;
	}
	namespace Assets
	{
		/**
		 * \brief manages project assets, but the user has to register the asses in the first place
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX AssetManager
		{
			friend class Infrastructure::Engine;

			/// assets table
			static std::map<std::string, IAssetPtr> _assetTable;

			/*
			 * \brief populates the table with the default assets
			 * \author Moustapha Saad
			 */
			static void addDefaultAssets();

			/**
			 * \brief performs memory cleanup before destruction
			 * \author Moustapha Saad
			 */
			static void cleanUp();
		public:
			/**
			 * \brief search the table for an asset
			 * \param name name of the asset
			 * \return IAsset pointer
			 * \author Moustapha Saad
			 */
			static IAsset* find(std::string name);

			/**
			 * \brief adds an asset to asset table
			 * \param asset asset shared pointer
			 * \author Moustapha Saad
			 */
			static void add(IAssetPtr asset);

			/**
			 * \brief adds an asset with a custom name, it actaully changes the name of the asset
			 * \param name name of the asset
			 * \param asset asset shared pointer
			 * \author Moustapha Saad
			 */
			static void add(std::string name,IAssetPtr asset);
		};
	}
}