#pragma once
#include "AccessException.h"
#include <iostream>
namespace Break{
	namespace Infrastructure{
		enum Permission{
			READ,WRITE,READ_WRITE
		};
		/**
		 * @class	Property
		 *
		 * @brief	A property.
		 *
		 * @author	Moustapha Saad
		 * @date	10/02/2015
		 *
		 * @tparam	Prop	Type of the property that it contains.
		 * @tparam	Obj 	Type of the object that holds this property.
		 */
 
		template<class Prop, class Obj, Permission permission>
		class Property{
 
			/**
			 * @typedef	Prop(Obj::* _get)()
			 *
			 * @brief	Defines an alias representing the get function.
			 */
 
			typedef Prop(Obj::* _get)();
 
			/**
			 * @typedef	void (Obj::* _set)(Prop)
			 *
			 * @brief	Defines an alias representing the set function.
			 */
 
			typedef void (Obj::* _set)(Prop);
 
			/** @brief	an instance of the class that holds the property. */
			Obj& instance;
 
			/** @brief	function pointer to the get function. */
			_get get;
 
			/** @brief	function pointer to the set function. */
			_set set;
 
 
			/**
			 * @fn	Prop Property::getVal()
			 *
			 * @brief	Gets the value from the object.
			 *
			 * @author	Moustapha Saad
			 * @date	10/02/2015
			 *
			 * @return	The value.
			 */
 
			Prop getVal(){
				if(permission == READ || permission == READ_WRITE)
					return (instance.*get)();
				else
					throw accessException("Can't perform operation due to protection levels");
			}
			Prop getVal()const{
				if(permission == READ || permission == READ_WRITE)
					return (instance.*get)();
				else
					throw accessException("Can't perform operation due to protection levels");
			}
 
			/**
			 * @fn	void Property::setVal(Prop& val)
			 *
			 * @brief	Sets a value.
			 *
			 * @author	Moustapha Saad
			 * @date	10/02/2015
			 *
			 * @param [in,out]	val	The value.
			 */
 
			void setVal(const Prop& val){
				if(permission == WRITE || permission == READ_WRITE)
					(instance.*set)(val);
				else
					throw accessException("Can't perform operation due to protection levels");
			}
 
		public:
 
			/**
			 * @fn	Property::Property(Obj& obj, _get g, _set s)
			 *
			 * @brief	Constructor.
			 *
			 * @author	Moustapha Saad
			 * @date	10/02/2015
			 *
			 * @param [in,out]	obj	The object.
			 * @param	g		   	The _get function.
			 * @param	s		   	The _set function.
			 */
 
			Property(Obj& obj, _get g, _set s):instance(obj), get(g), set(s){
			}
 
			/**
			 * @fn	operator Property::Prop()
			 *
			 * @brief	Cast that converts the given  to a Prop.
			 *
			 * @author	Moustapha Saad
			 * @date	10/02/2015
			 *
			 * @return	The result of the operation.
			 */
 
			operator Prop(){
				return getVal();
			}
 
			operator Prop()const{
				return (getVal());
			}
 
			/**
			 * @fn	void Property::operator=(Prop& val)
			 *
			 * @brief	Assignment operator.
			 *
			 * @author	Moustapha Saad
			 * @date	10/02/2015
			 *
			 * @param [in,out]	val	The value.
			 */
			Prop operator->()const{
				return getVal();
			}
			void operator =(const Prop& val){
				setVal(val);
			}
 
			Prop operator +=(const Prop& val){
				setVal(getVal()+val);
				return *this;
			}
			Prop operator -=(const Prop& val){
				setVal(getVal()-val);
				return *this;
			}
			Prop operator *=(const Prop& val){
				setVal(getVal()*val);
				return *this;
			}
			Prop operator /=(const Prop& val){
				setVal(getVal()/val);
				return *this;
			}
			Prop operator %=(const Prop& val){
				setVal(getVal()%val);
				return *this;
			}
			friend std::ostream& operator<< (std::ostream& stream, const Prop& val) {
				stream<<val;
				return stream;
			}
 
		};
	}
}