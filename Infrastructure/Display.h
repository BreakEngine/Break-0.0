#pragma once
#include "IDisplay.h"
namespace Break
{

	namespace Infrastructure{
		//template display to handle the gl and dx display handle
		template<class T>
		class Display:public IDisplay{
		protected:
			T handle;
		public:
			Display(){

			}
			~Display(){

			}
			T getHandle(){
				return handle;
			}
			
		};
	}
}