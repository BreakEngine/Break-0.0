#pragma once
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <random>
#include <cmath> // abs, sqrt
#include <cassert> // assert
#include <algorithm> // max, min
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "GlobalDefinitions.h"

namespace Break
{
		typedef float real;
		typedef double real64;
		typedef signed char	int8;
		typedef signed short int16;
		typedef signed int int32;
		typedef unsigned char uint8;
		typedef unsigned short uint16;
		typedef unsigned int uint32;

		#ifdef WIN32 // these types are not standard, only exist in windows
		typedef __int64 int64;
		typedef unsigned __int64 uint64;
		#endif
		typedef float f32;
		typedef double f64;

		/*
		constat to use..
		*/

		//to be moved to physics engine class since it can theoratically change in runtime
		const f32 gravityScale = 5.0f;
		const glm::vec2 gravity( 0, 10.0f * gravityScale );
	namespace Infrastructure
	{

		struct BREAK_API_EX Mat2
			{
				union
				{
					struct
					{
						real m00, m01;
						real m10, m11;
					};

					real m[2][2];
					real v[4];
				};

				Mat2( ) {}
				Mat2( real radians )
				{
					real c = std::cos( radians );
					real s = std::sin( radians );

					m00 = c; m01 = -s;
					m10 = s; m11 =  c;
				}

				Mat2( real a, real b, real c, real d )
					: m00( a ), m01( b )
					, m10( c ), m11( d )
				{
				}

				void Set( real radians )
				{
					real c = std::cos( radians );
					real s = std::sin( radians );

					m00 = c; m01 = -s;
					m10 = s; m11 =  c;
				}

				Mat2 Abs( void ) const
				{
					return Mat2( std::abs( m00 ), std::abs( m01 ), std::abs( m10 ), std::abs( m11 ) );
				}

				glm::vec2 AxisX( void ) const
				{
					return glm::vec2( m00, m10 );
				}

				glm::vec2 AxisY( void ) const
				{
					return glm::vec2( m01, m11 );
				}

				Mat2 Transpose( void ) const
				{
					return Mat2( m00, m10, m01, m11 );
				}

				const glm::vec2 operator*( const glm::vec2& rhs ) const
				{
					return glm::vec2( m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y );
				}

				const Mat2 operator*( const Mat2& rhs ) const
				{
					// [00 01]  [00 01]
					// [10 11]  [10 11]

					return Mat2(
						m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
						m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
						m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
						m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
					);
				}
			};

		class BREAK_API_EX MathUtils
		{
		public:

			static inline real toDegrees(real rad)
			{
				return rad * (180/PI);
			}
			static inline real toRadians(real deg)
			{
				return deg * (PI/180);
			}
			static inline real LenSqr( glm::vec2 _vec ) 
			{
				return _vec.x * _vec.x + _vec.y * _vec.y;
			}



			static inline real Len( glm::vec2 _vec ) 
			{
				return std::sqrt( _vec.x * _vec.x + _vec.y * _vec.y );
			}


			static inline glm::vec2 Normalize( glm::vec2 _vec )
			{
				real len = Len( _vec );

				if(len > EPSILON)
				{
					real invLen = 1.0f / len;
					_vec.x *= invLen;
					_vec.y *= invLen;
				}

				return _vec;
			}


			static inline glm::vec2 Min( const glm::vec2& a, const glm::vec2& b )
			{
				return glm::vec2( std::min( a.x, b.x ), std::min( a.y, b.y ) );
			}

			static inline glm::vec2 Max( const glm::vec2& a, const glm::vec2& b )
			{
				return glm::vec2( std::max( a.x, b.x ), std::max( a.y, b.y ) );
			}

			static inline real Dot( const glm::vec2& a, const glm::vec2& b )
			{
				return a.x * b.x + a.y * b.y;
			}

			static inline real DistSqr( const glm::vec2& a, const glm::vec2& b )
			{
				glm::vec2 c = a - b;
				return Dot( c, c );
			}

			static inline glm::vec2 Cross( const glm::vec2& v, real a )
			{
				return glm::vec2( a * v.y, -a * v.x );
			}

			static inline glm::vec2 Cross( real a, const glm::vec2& v )
			{
				return glm::vec2( -a * v.y, a * v.x );
			}

			static inline real Cross( const glm::vec2& a, const glm::vec2& b )
			{
				return a.x * b.y - a.y * b.x;
			}



			// Comparison with tolerance of EPSILON
			static inline bool Equal( real a, real b )
			{
				// <= instead of < for NaN comparison safety
				return std::abs( a - b ) <= EPSILON;
			}



			static inline real Sqr( real a )
			{
				return a * a;
			}



			static inline real Clamp( real min, real max, real a )
			{
				if (a < min) return min;
				if (a > max) return max;
				return a;
			}



			static inline int32 Round( real a )
			{
				return (int32)(a + 0.5f);
			}


			/*
			needed to use,,
			*/
			static inline real Random( real l, real h )
			{
				std::random_device device;
				std::mt19937 gen(device());
				std::uniform_real_distribution<> dis(l,h);
				real a = (real)dis(gen);
				return a;
			}

			static inline bool BiasGreaterThan( real a, real b )
			{
				const real k_biasRelative = 0.95f;
				const real k_biasAbsolute = 0.01f;
				return a >= b * k_biasRelative + a * k_biasAbsolute;
			}


			static const float PI;
			static const float EPSILON;


			static bool counterClockWiseWinding(glm::vec2 a, glm::vec2 b, glm::vec2 c)
			{
				return counterClockWiseWinding(glm::vec3(a.x,a.y,0),glm::vec3(b.x,b.y,0),glm::vec3(c.x,c.y,0));
			}
			static bool counterClockWiseWinding(glm::vec3 a, glm::vec3 b, glm::vec3 c)
			{
				auto axis_x = glm::normalize(b-a);
				auto axis_y = glm::normalize(c-a);
				auto axis_z = glm::cross(axis_x, axis_y);

				glm::mat3 object_transform;
				object_transform[0] = axis_x;
				object_transform[1] = axis_y;
				object_transform[2] = axis_z;

				auto obj_to_world = glm::inverse(object_transform);

				auto normal = obj_to_world*axis_z;
				if(normal.z>0.0f)
					return true;
				else
					return false;
			}
		};
	}
}