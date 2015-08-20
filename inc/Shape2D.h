#pragma once
#include "Geometry.h"
#include "Pixels.h"
#include "Vertex2DPosColorTex.h"
#include "Texture.h"
#include "IndexSet.h"
#include "Transformable.h"


namespace Break
{
	namespace Graphics
	{
		///represents a shape2D
		class Shape2D: public GXWrapper::IDrawable, public Transformable
		{
		protected:
			///color of the shape
			glm::vec4 _fillColor;
			///texture of the shape
			GXWrapper::TexturePtr _texture;

			///shape vertices
			GXWrapper::VertexSet<Assets::Vertex2DPosColorTex> _vertices;
			///shape indices
			GXWrapper::IndexSet _indices;

			///geometry instance
			GXWrapper::GeometryPtr _geometry;

			///update bool
			bool _needUpdate;
		public:

			///default constructor
			Shape2D();

			virtual ~Shape2D();

			/**
			 * \brief appends a vertex to shape
			 * \param v vertex position
			 * \param color vertex color
			 * \param tex vertex texCoord
			 * \author Moustapha Saad
			 */
			void append(glm::vec2 v, glm::vec4 color = glm::vec4(0,0,0,-1), glm::vec2 tex = glm::vec2(0));

			///appends a vertex to shape
			void append(float x, float y);

			///sets a texture to shape
			void setTexture(std::shared_ptr<GXWrapper::Texture> texture);
			///gets the texture of the shape
			GXWrapper::Texture* getTexture();

			///sets the position of this shape
			void setPosition(float x, float y);
			///sets a scale
			void setScale(float x, float y);
			///sets a rotate
			void rotate(float angle);

			///sets the color of all vertices
			void setFillColor(GXWrapper::Color color);

			///performs a draw call
			virtual void draw()override;
		};
	}
}