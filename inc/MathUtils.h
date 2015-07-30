#pragma once
#include <glm/common.hpp>
#include <glm/glm.hpp>

namespace Break
{
	namespace Infrastructure
	{
		class MathUtils
		{
		public:
			static bool counterClockWiseWinding(glm::vec2 a, glm::vec2 b, glm::vec2 c)
			{
				return counterClockWiseWinding(glm::vec3(a.x,a.y,0),glm::vec3(b.x,b.y,0),glm::vec3(c.x,c.y,0));
			}
			static bool counterClockWiseWinding(glm::vec3 a, glm::vec3 b, glm::vec3 c)
			{
				auto axis_x = glm::normalize(b-a);
				auto axis_y = glm::normalize(c-a);
				auto axis_z = glm::cross(axis_x, axis_y);

				glm::mat3 object_transform;
				object_transform[0] = axis_x;
				object_transform[1] = axis_y;
				object_transform[2] = axis_z;

				auto obj_to_world = glm::inverse(object_transform);

				auto normal = obj_to_world*axis_z;
				if(normal.z>0.0f)
					return true;
				else
					return false;
			}
		};
	}
}