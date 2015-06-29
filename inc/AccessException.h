#pragma once
#include <exception>
#include <string>
namespace Break{
	namespace Infrastructure{

		class accessException:public std::exception{

		private:
			std::string _msg;

		public:
			explicit accessException(const char* message):_msg(message){

			}

			explicit accessException(const std::string& message):_msg(message){

			}

			virtual ~accessException()throw(){}

			virtual const char* what() const throw(){
				return _msg.c_str();
			}

		};

	}

}