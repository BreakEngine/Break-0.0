#pragma once
#include <string>
namespace Break
{
	class Object
	{
	public:
		std::string id;

		Object():id("Object"){}
		Object(std::string name):id(name){}
		virtual ~Object(){id.clear();}
	};
}