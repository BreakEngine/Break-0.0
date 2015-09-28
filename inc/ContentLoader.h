#pragma once
#include "IAsset.h"
#include "Image.h"
#include <string>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Assets{
		/**
		 * \brief loads anytype of resource
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX ContentLoader{
		public:
			/**
			 * \brief loads any type of resource
			 * \param file path to resource file
			 * \return shared_ptr of resource type
			 * \author Moustapha Saad
			 */
			template <class T>
			static std::shared_ptr<T> load(std::string file);

		};
	}
}