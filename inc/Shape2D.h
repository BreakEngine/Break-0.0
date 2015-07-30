#pragma once
#include "Geometry.h"
#include "Pixels.h"
#include "Vertex2DPos.h"
#include "IndexSet.h"

namespace Break
{
	namespace Renderer
	{
		class Shape2D: public GXWrapper::IDrawable
		{
		protected:
			GXWrapper::GeometryPtr _geometry;
			glm::vec4 _fillColor;


			GXWrapper::VertexSet<Assets::Vertex2DPos> _vertices;

			bool _needUpdate;
		public:
			Shape2D();
			virtual ~Shape2D();

			void append(glm::vec2 v);
			void append(float x, float y);

			void setFillColor(GXWrapper::Color color);

			virtual void draw(GXWrapper::Primitive::Mode mode = GXWrapper::Primitive::NORMAL)override;
		};
	}
}