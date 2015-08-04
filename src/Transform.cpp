#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>
using namespace Break::Graphics;
using namespace glm;

Transform::Transform(const glm::vec3 pos, const glm::quat rot, glm::vec3 scl)
{
	position = pos;
	rotation = rot;
	scale = scl;
}

Transform::Transform(const Transform& val)
{
	position = val.position;
	rotation = val.rotation;
	scale = val.scale;
}

glm::mat4 Transform::getMatrix()
{
	mat4 translation = translate(mat4(1),position);
	mat4 scl = glm::scale(mat4(1),scale);
	mat4 rot = glm::mat4_cast(rotation);

	return translation*rot*scl;
}

void Transform::rotate(const glm::vec3 axis, float angle)
{
	rotation *= glm::angleAxis(angle,axis);
}

void Transform::move(const glm::vec3 dir, float val)
{
	position += dir*val;
}

glm::vec4 Transform::getLookAt(glm::vec3 point, glm::vec3 up)
{
	return vec4(0);
}