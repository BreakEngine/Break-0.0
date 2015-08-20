#pragma once
#include"TimeStep.h"
#include<memory>

namespace Break{
	namespace Infrastructure{
		///renderer class to determine each segmant of the gameloop
		class IRenderer{
		public:
			///public default constructor
			IRenderer();
			///public default destructor
			virtual ~IRenderer();
			/*!
			 * \function input
			 *
			 * \brief determines the default input function of the default renderer
			 *
			 * \author Moustapha Saad
			 */
			virtual void input();
			/*!
			 * \function update(TimeStep)
			 *
			 * \brief determines the update function of the default renderer
			 *
			 * \author Moustapha Saad
			 */
			virtual void update(TimeStep);
			/*!
			 * \function render()
			 *
			 * \brief determines the render function of the default renderer
			 *
			 * \author Moustapha Saad
			 */
			virtual void render();
		};
		typedef std::shared_ptr<IRenderer> IRendererPtr;
	}
}