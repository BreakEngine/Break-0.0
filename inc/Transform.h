#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace Break
{
	namespace Graphics
	{
		class Transform
		{
		protected:
			glm::mat4 matrix;
		public:
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scale;

			Transform(const glm::vec3 pos = glm::vec3(0),
				const glm::quat rot = glm::quat(),
				glm::vec3 scle = glm::vec3(1,1,1));
			
			Transform(const Transform& val);

			glm::mat4 getMatrix();

			void rotate(const glm::vec3 axis, float angle);

			void move(const glm::vec3 dir, float val);

			glm::vec4 getLookAt(glm::vec3 point,glm::vec3 up);
		};
	}
}