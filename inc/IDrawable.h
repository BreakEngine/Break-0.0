#pragma once
#include "GlobalDefinitions.h"

namespace Break{
	namespace GXWrapper{
		/**
		 * \brief API Primitve
		 * \author Mohammed Shaalan
		 */
		struct BREAK_API_EX Primitive{

			///primitive type
			enum Type
			{
				POINTS = 0,
				LINES = 1,
				LINE_STRIP = 2,
				//LINE_LOOP = 3,
				TRIANGLES = 4
				//TRIANGLE_STRIP = 5
				//TRIANGLE_FAN = 6
			};

			///primitve Mode
			enum Mode
			{
				NORMAL = 0,
				INDEXED = 1,
				NORMAL_INSTANCED = 2,
				INDEX_INSTANCED
			};

		};

		/**
		 * \brief draw interface
		 * \author Mohammed Shaalan
		 */
		class BREAK_API_EX IDrawable
		{
		public:

			/**
			 * \brief abstract draw function
			 * \author Mohammed Shaalan
			 */
			virtual void draw() = 0;
		};

	}
}
