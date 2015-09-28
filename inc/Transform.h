#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "GlobalDefinitions.h"

namespace Break
{
	namespace Graphics
	{

		/**
		 * \brief reperesents a transformation matrix of an object
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX Transform
		{
		protected:
			///transformation matrix
			glm::mat4 matrix;
		public:
			///postion vector
			glm::vec3 position;
			///rotation quaternion
			glm::quat rotation;
			///scale vector
			glm::vec3 scale;

			///default constructor
			Transform(const glm::vec3 pos = glm::vec3(0),
				const glm::quat rot = glm::quat(),
				glm::vec3 scle = glm::vec3(1,1,1));

			///copy constructor
			Transform(const Transform& val);

			///transformation matrix getter
			glm::mat4 getMatrix();

			/**
			 * \brief rotates the object around some axis
			 * \param axis the axis that this object will rotate around it
			 * \param angle the angle it will rotate in degrees
			 * \author Moustapha Saad
			 */
			void rotate(const glm::vec3 axis, float angle);

			///moves the object in some direction by some amount
			void move(const glm::vec3 dir, float val);

			///returns a look at roataion vecto
			glm::vec4 getLookAt(glm::vec3 point,glm::vec3 up);
		};
	}
}