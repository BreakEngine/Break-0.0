#pragma once
#include <exception>
#include <string>
namespace Break{
	namespace Infrastructure{
		class accessError:public std::exception{
		private:
			std::string _msg;
		public:
			explicit accessError(const char* message):_msg(message){

			}

			explicit accessError(const std::string& message):_msg(message){

			}

			virtual ~accessError()throw(){}

			virtual const char* what() const throw(){
				return _msg.c_str();
			}
		};
	}
}