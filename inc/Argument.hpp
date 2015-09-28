#pragma once
#include "GlobalDefinitions.h"
#include "GPU_ISA.hpp"
#include "IGPUHandle.h"
#include "MemoryLayout.h"
#include "Image.h"
#include "IDrawable.h"
#include "Texture.h"

namespace Break
{
	namespace Renderer
	{

		class Arg
		{
			union 
			{
				bool boolean;
				u8 u8_val;
				u16 u16_val;
				u32 u32_val;
				u64 u64_val;
				
				s8 s8_val;
				s16 s16_val;
				s32 s32_val;
				s64 s64_val;

				real real_val;
				real64 real64_val;

				void* ptr;
				GPU_ISA tag;
				Infrastructure::IGPUHandle* gpu_handle;
				GXWrapper::MemoryLayout* mem_layout;
				GXWrapper::Image* img;
				GXWrapper::Primitive::Type primitive;

				GXWrapper::TextureAddressMode address_mode;
				GXWrapper::TextureFilter texture_filter;
				GXWrapper::CompareFunction compare_function;

				GXWrapper::Color* color;

				std::string* str;
			};
		public:

			Arg(bool val):boolean(val){}
			Arg(u8 val):u8_val(val){}
			Arg(u16 val):u16_val(val){}
			Arg(u32 val):u32_val(val){}
			Arg(u64 val):u64_val(val){}

			Arg(s8 val):s8_val(val){}
			Arg(s16 val):s16_val(val){}
			Arg(s32 val):s32_val(val){}
			Arg(s64 val):s64_val(val){}

			Arg(real val):real_val(val){}
			Arg(real64 val):real64_val(val){}

			Arg(void* val):ptr(val){}

			Arg(GPU_ISA val):tag(val){}

			Arg(Infrastructure::IGPUHandle* val):gpu_handle(val){}

			Arg(GXWrapper::MemoryLayout* val):mem_layout(val){}

			Arg(std::string* val):str(val){}

			Arg(GXWrapper::Image* val):img(val){}

			Arg(GXWrapper::Primitive::Type val): primitive(val){}

			Arg(GXWrapper::TextureAddressMode val):address_mode(val){}

			Arg(GXWrapper::TextureFilter val):texture_filter(val){}

			Arg(GXWrapper::CompareFunction val):compare_function(val){}

			Arg(GXWrapper::Color* val):color(val){}


			operator bool(){
				return boolean;
			}

			operator u8()
			{
				return u8_val;
			}

			operator u16()
			{
				return u16_val;
			}

			operator u32()
			{
				return u32_val;
			}

			operator u64()
			{
				return u64_val;
			}

			operator s8()
			{
				return s8_val;
			}

			operator s16()
			{
				return s16_val;
			}

			operator s32()
			{
				return s32_val;
			}

			operator s64()
			{
				return s64_val;
			}

			operator real()
			{
				return real_val;
			}

			operator real64()
			{
				return real64_val;
			}

			operator void*(){
				return ptr;
			}

			operator GPU_ISA(){
				return tag;
			}

			operator Infrastructure::IGPUHandle*(){
				return gpu_handle;
			}

			operator GXWrapper::MemoryLayout*(){
				return mem_layout;
			}

			operator std::string*(){
				return str;
			}

			operator GXWrapper::Image*(){
				return img;
			}

			operator GXWrapper::Primitive::Type()
			{
				return primitive;
			}

			operator GXWrapper::TextureAddressMode()
			{
				return address_mode;
			}

			operator GXWrapper::TextureFilter()
			{
				return texture_filter;
			}

			operator GXWrapper::CompareFunction()
			{
				return compare_function;
			}

			operator GXWrapper::Color*(){
				return color;
			}
		};
	}
}