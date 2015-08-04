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
			static IAsset* find(std::string);
			static void add(IAssetPtr);
			static void add(std::string name,IAssetPtr res);
		};
	}
}