#pragma once
#include <string>
#include <memory>
#include "Property.h"
namespace Break{
	namespace Infrastructure{
		class IDisplay
		{
		protected:

			//window dimensions
			unsigned int _width, _height;

			std::string _title;
		public:
			std::string getTitle();
			unsigned int getWidth();
			unsigned int getHeight();
			void setTitle(std::string val);
			void setWidth(unsigned int val);
			void setHeight(unsigned int val);

			IDisplay(unsigned int x = 800, unsigned int y =600, std::string t = "Break Engine");
			virtual ~IDisplay();
			//returns aspect ratio of window
			float aspectRatio();

		};
		typedef std::shared_ptr<IDisplay> IDisplayPtr;

	}
}