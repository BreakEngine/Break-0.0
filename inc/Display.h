#pragma once
#include "IDisplay.h"
#include "GlobalDefinitions.h"

namespace Break
{

	namespace Infrastructure{
		///template display to handle the gl and dx display handle
		template<class T>
		class BREAK_API_EX Display:public IDisplay{
		protected:
			T handle;
		public:
			Display(){

			}
			Display(const IDisplay& val){
				_width = val.getWidth();
				_height = val.getHeight();
				_title = val.getTitle();
			}
			~Display(){

			}
			T getHandle(){
				return handle;
			}
			void setHandle(T val){
				handle = val;
			}
		};
	}
}