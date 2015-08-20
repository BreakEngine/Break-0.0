#pragma once
#include "Pixels.h"
#include "IAsset.h"
#include <memory>

namespace Break{
	namespace GXWrapper{

		/**
		 * \brief represents an image resource
		 * \author Moustapha Saad
		 */
		class Image:public Assets::IAsset{

			///pointer to image pixels
			Pixel* _data;

			///image info, width, height, depth, pixels size
			unsigned int _width,_height,_depth,_dataSize;

			///To Prevent copying data
			Image(const Image& val);


			/**
			 * \brief width setter
			 * \param val new width
			 * \author Moustapha Saad
			 */
			void setWidth(unsigned int val);

			/**
			 * \brief height setter
			 * \param val new height
			 * \author Moustapha Saad
			 */
			void setHeight(unsigned int val);

			/**
			 * \brief height setter
			 * \param val new height
			 * \author Moustapha Saad
			 */
			void setDepth(unsigned int val);
		public:
			///defualt constructor
			Image();

			/**
			 * \brief init constructor
			 * \param data pointer to image pixels
			 * \param width width of the image
			 * \param height height of the image (OPTIONAL, in case of 1D image)
			 * \param depth depth of the image (OPTIONAL, in case of 2D image)
			 * \author Moustapha Saad
			 */
			Image(Pixel* data,unsigned int width,unsigned int height=1, unsigned int depth=1);

			/**
			 * \brief empty image constructor
			 * \param width width of the image
			 * \param height height of the image (OPTIONAL, in case of 1D image)
			 * \param depth depth of the image (OPTIONAL, in case of 2D image)
			 * \author Moustapha Saad
			 */
			Image(unsigned int width,unsigned int height=1, unsigned int depth=1);

			///virtual default destructor
			virtual ~Image();

			/**
			 * \brief gets pixels of the image
			 * \author Moustapha Saad
			 */
			Pixel* getPixels();

			/**
			 * \brief width getter
			 * \return width of the image
			 * \author Moustapha Saad
			 */
			unsigned int getWidth();

			/**
			 * \brief height getter
			 * \return height of the image
			 * \author Moustapha Saad
			 */
			unsigned int getHeight();

			/**
			 * \brief depth getter
			 * \return depth of the image
			 * \author Moustapha Saad
			 */
			unsigned int getDepth();

			/**
			 * \brief pixel count getter
			 * \return pixel count in this image
			 * \author Moustapha Saad
			 */
			unsigned int getSize();

			/**
			 * \brief single pixel getter
			 * \param x x index of the image
			 * \param y y index of the image (OPTIONAL, in case of 1D image)
			 * \param z z index of the image (OPTIONAL, in case of 2D image)
			 * \return pixel reference
			 * \author Moustapha Saad
			 */
			Pixel& getPixel(unsigned int x, unsigned int y=0, unsigned int z=0);

			/**
			 * \brief returns a new image object with the same data
			 * \author Moustapha Saad
			 */
			std::shared_ptr<Image> clone();
		};

		///type alias to shared_ptr of Image
		typedef std::shared_ptr<Image> ImagePtr;

	}
}