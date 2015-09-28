#pragma once

#include "ISet.h"
#include "GeometryData.h"
#include <memory>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Renderer
	{
		class SpriteBatcher;
	}
	namespace GXWrapper{

		/**
		 * \brief represents GPU Geometry class, it's the most basic class to draw it just holds raw vertex and index data
		 * \author Moustapha Saad
		 */

		class BREAK_API_EX Geometry: public IDrawable, Infrastructure::GPUResource{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
			friend class Renderer::SpriteBatcher;
		private:

			///memory layout of the vertex
			MemoryLayout _declaration;
			///Geometry data handle
			GeometryData _geometryData;
		protected:
			/**
			 * \brief create function that creates the corresponding part on GPU
			 * \author Moustapha Saad
			 */
			virtual bool createGPUResource()override;
		public:

			/**
			 * \brief constructor from sets
			 * \param vertices set of vertices
			 * \param indices set of indices
			 * \param type primitve type of this geometry
			 * \author Moustapha Saad
			 */
			Geometry(ISet& vertices, ISet* indices,Primitive::Type type);

			/**
			 * \brief constructor from buffers
			 * \param vb vertex buffer
			 * \param layout memory layout of the vertex buffer
			 * \param ib index buffer
			 * \param type primitive type of this geometry
			 * \author Moustapha Saad
			 */
			Geometry(VertexBuffer* vb,MemoryLayout layout,IndexBuffer* ib,Primitive::Type type);

			/**
			 * \brief copy constructor
			 * \author Moustapha Saad
			 */
			Geometry(const Geometry& val);

			/**
			 * \brief default destructor
			 */
			~Geometry();

			/**
			 * \brief vertices getter
			 * \return a pointer to vertices data type
			 * \author Moustapha Saad
			 */
			template<class T>
			T* getVertices(){
				T* head = reinterpret_cast<T*>(_geometryData.vertices->getData(_geometryData.verticesOffset));
				return head;
			}

			/**
			 * \brief indices getter
			 * \return unsigned int pointer to buffer data
			 * \author Moustapha Saad
			 */
			unsigned int* getIndices();

			/**
			 * \brief vertices count getter
			 * \return count of vertices in this geometry
			 * \author Moustapha Saad
			 */
			unsigned int getVerticesCount();

			/**
			 * \brief indices count getter
			 * \return count of indices in this geometry
			 * \author Moustapha Saad
			 */
			unsigned int getIndicesCount();

			/**
			 * \brief Memory Layout getter
			 * \return Memory layout of this geometry
			 * \author Moustapha Saad
			 */
			MemoryLayout getMemoryLayout();

			/**
			 * \brief returns geometry data handle
			 * \return Geometry reference
			 * \author Moustpaha Saad
			 */
			GeometryData& getGeometryData();

			/**
			 * \brief draw funciton that invokes a draw call of this geometry
			 * \author Moustapha Saad
			 */
			virtual void draw()override;
		};
		//type alias of geometry shared_ptr
		typedef std::shared_ptr<Geometry> GeometryPtr;
	}
}