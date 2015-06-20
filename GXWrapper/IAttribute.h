#pragma once

#include <glm/glm.hpp>
#include "../Infrastructure/GlobalDefinitions.h"

namespace Break{

	namespace GXWrapper{

		class Vertex;
		/*
		 * Attribute Class that generalize vertex attribute
		 */
		class IAttribute{
			friend class Vertex;

			//byte pointer to the data
			Infrastructure::byte* _data;
			//size of the array
			unsigned int _size;
			//indicate whether it's just a handle to buffer or not
			bool isHandle;

		public:
			//cast constructor
			IAttribute(int);
			IAttribute(float);
			IAttribute(double);
			IAttribute(bool);
			IAttribute(glm::vec2);
			IAttribute(glm::vec3);
			IAttribute(glm::vec4);
			IAttribute();
			IAttribute(const IAttribute& val);

			virtual ~IAttribute();

			//implicit cast
			operator int&();
			operator float&();
			operator double&();
			operator bool&();
			operator glm::vec2&();
			operator glm::vec3&();
			operator glm::vec4&();

			IAttribute& operator=(const IAttribute& val);

			unsigned int getSize();
			Infrastructure::byte* getData();
			void clean();
			
		};

	}

}