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
		class Shape2D: public GXWrapper::IDrawable, public Transformable
		{
		protected:
			glm::vec4 _fillColor;
			GXWrapper::TexturePtr _texture;


			GXWrapper::VertexSet<Assets::Vertex2DPosColorTex> _vertices;
			GXWrapper::IndexSet _indices;

			GXWrapper::GeometryPtr _geometry;

			bool _needUpdate;
		public:
			Shape2D();
			virtual ~Shape2D();

			void append(glm::vec2 v, glm::vec4 color = glm::vec4(0,0,0,-1), glm::vec2 tex = glm::vec2(0));
			void append(float x, float y);

			void setTexture(std::shared_ptr<GXWrapper::Texture> texture);
			GXWrapper::Texture* getTexture();

			void setPosition(float x, float y);
			void setScale(float x, float y);
			void rotate(float angle);

			void setFillColor(GXWrapper::Color color);

			virtual void draw(GXWrapper::Primitive::Mode mode = GXWrapper::Primitive::NORMAL)override;
		};
	}
}