#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace Break{
	namespace Infrastructure{
		//define byte
		typedef unsigned char byte;
		typedef std::shared_ptr<byte> bytePtr;

		//define color
		typedef glm::vec4 color;
	}
	//unsigned int type def.
	typedef unsigned int uint;
}