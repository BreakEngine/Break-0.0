#pragma once

#include <memory>
#include <glm/glm.hpp>
#include  <stdint.h>
#include <vector>
#include <map>

#if defined(WIN32) ||defined(_WIN32) || defined(__WIN32__)|| defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS
#elif defined(__linux__) || defined(__unix__)
#define OS_LINUX
#endif

namespace Break{

	//define byte
	typedef unsigned char byte;
	typedef std::shared_ptr<byte> bytePtr;

	//define color
	typedef glm::vec4 color;

	//unsigned int type def.
	typedef int8_t s8;
	typedef int16_t s16;
	typedef int32_t s32;
	typedef int64_t s64;

	typedef uint8_t u8;
	typedef uint16_t u16;
	typedef uint32_t u32;
	typedef uint64_t u64;

	typedef float real;
	typedef double real64;

	template<class T>
	using list = std::vector<T>;

	template<class key, class value>
	using dictionary =  std::map<key, value>;

	#define null nullptr

#ifdef OS_WINDOWS
#define BREAK_API_EX __declspec(dllexport)
#endif

#ifdef OS_LINUX
#define BREAK_API_EX 
#endif

}