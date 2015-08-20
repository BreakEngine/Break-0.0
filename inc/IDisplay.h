#pragma once
#include <string>
#include <memory>
#include "Property.h"
namespace Break{
	namespace Infrastructure{
		/**
		 * \brief represents a display
		 * \author Moustapha Saad
		 */
		class IDisplay
		{
		protected:

			///window dimensions
			unsigned int _width, _height;
			///window title
			std::string _title;
		public:

			/**
			 * \brief title getter
			 * \return diaply title
			 * \author Moustapha Saad
			 */
			std::string getTitle()const;

			/**
			 * \brief width getter
			 * \return diaply width
			 * \author Moustapha Saad
			 */
			unsigned int getWidth()const;

			/**
			 * \brief height getter
			 * \return diaply height
			 * \author Moustapha Saad
			 */
			unsigned int getHeight()const;

			/**
			 * \brief title setter
			 * \param val title of the display
			 * \author Moustapha Saad
			 */
			void setTitle(std::string val);

			/**
			 * \brief width setter
			 * \param val width of the diaply
			 * \author Moustapha Saad
			 */
			void setWidth(unsigned int val);

			/**
			 * \brief height setter
			 * \param val height of the display
			 * \author Moustapha Saad
			 */
			void setHeight(unsigned int val);

			/**
			 * \brief default construtor
			 * \param x display width (OPTIONAL) default = 800
			 * \param y display height (OPTIONAL) default = 600
			 * \param t display title (OPTIONAL) default = "Break Engine"
			 * \author Moustapha Saad
			 */
			IDisplay(unsigned int x = 800, unsigned int y =600, std::string t = "Break Engine");

			//virtual default destrcutor
			virtual ~IDisplay();

			/**
			 * \brief returns aspect ratio of this display
			 * \return apect ration of the display
			 * \author Moustapha Saad
			 */
			float aspectRatio();

		};
		///type alias of diapl y shared_ptr
		typedef std::shared_ptr<IDisplay> IDisplayPtr;

	}
}