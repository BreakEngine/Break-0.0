#pragma once
#include <exception>
#include <string>
namespace Break{
	namespace Infrastructure{

		/*
		 * \brief exception class for unauthorized access of data
		 * \author Moustapha Saad
		 */
		class accessException:public std::exception{

		private:
			///msg string that will be sent with exception
			std::string _msg;

		public:
			/**
			 * \brief consturctor that accepts message
			 * \param message c-style string represents the message
			 * \author Moustapha Saad
			 */
			explicit accessException(const char* message):_msg(message){

			}

			/**
			 * \brief consturctor that accepts message
			 * \param message cpp-string string represents the message
			 * \author Moustapha Saad
			 */
			explicit accessException(const std::string& message):_msg(message){

			}

			/**
			 * \brief virtual destructor
			 * \author Moustapha Saad
			 */
			virtual ~accessException()throw(){}

			/**
			 * \brief returns a message of the exception
			 * \return const char*
			 * \author Moustapha Saad
			 */
			virtual const char* what() const throw(){
				return _msg.c_str();
			}

		};

	}

}