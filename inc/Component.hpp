#pragma once
#include <Object.hpp>
namespace Break
{
	namespace Graphics{
		class Entity;
		class Component:public Object
		{
		public:
			Entity* gameEntity;

			Component(std::string name):Object(name){gameEntity = nullptr;}
			Component():Object(){gameEntity = nullptr;}

			virtual ~Component(){gameEntity = nullptr;}
		};
		typedef std::shared_ptr<Component> ComponentPtr;

	}
}