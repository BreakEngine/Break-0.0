#pragma once
#include <exception>
#include <string>

namespace Break{
	namespace GXWrapper{
		class GPUException : public std::exception{
		private:
			std::string _msg;
		public:
			explicit GPUException(const char* message):_msg(message){

			}

			explicit GPUException(const std::string& message):_msg(message){

			}
			virtual ~GPUException()throw(){
				
			}

			virtual const char* what()const throw(){
				return _msg.c_str();
			}
		};
	}
}