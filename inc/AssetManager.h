#pragma once
#include <map>
#include "IAsset.h"

namespace Break
{
	namespace Infrastructure
	{
		class Engine;
	}
	namespace Assets
	{
		class AssetManager
		{
			friend class Infrastructure::Engine;
			static std::map<std::string, IAssetPtr> _assetTable;

			static void addDefaultAssets();
			static void cleanUp();
		public:
			static IAssetPtr find(std::string);
			static void add(IAsset*);
			static void add(std::string name,IAsset* res);
		};
	}
}