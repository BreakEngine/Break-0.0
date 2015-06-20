#pragma once
#include <exception>
#include <string>

namespace Break{
	namespace Infrastructure{
		class MemoryException:public std::exception{
		protected:
			std::string _msg;
		public:
			explicit MemoryException(const char* message):_msg(message){

			}
			explicit MemoryException(const std::string& message):_msg(message){

			}

			virtual ~MemoryException()throw(){}

			virtual const char* what() const throw(){
				return _msg.c_str();
			}
		};
	}
}