#pragma once
#include "Vertex2DPosColorTex.h"
#include "VertexSet.h"
#include "Texture2D.h"
#include "Geometry.h"
#include "IndexSet.h"
#include "Rect.h"

namespace Break
{
	namespace Graphics
	{
		class SpriteBatch
		{
		private:
			static const unsigned int _limit = 2000;
			unsigned int _count,vCount,iCount;
			GXWrapper::VertexSet<Assets::Vertex2DPosColorTex> _vertices;
			GXWrapper::IndexSet _indices;
			GXWrapper::GeometryPtr _geometry;
			GXWrapper::Texture2D* _texture;
			GXWrapper::Shader* _shader;

			bool _customShader;
			void checkFlush(GXWrapper::Texture2D* texture);
			glm::vec2 rotatePoint(glm::vec2 point, float angle);
		public:
			SpriteBatch(GXWrapper::ShaderPtr shader=nullptr);
			~SpriteBatch();

			void begin();
			void draw(GXWrapper::Texture2D*,int x, int y,GXWrapper::Color color);
			void draw(GXWrapper::Texture2D*,int x, int y,int width, int height,GXWrapper::Color color);
			void draw(GXWrapper::Texture2D*,Rect dest,float angle,GXWrapper::Color color);
			void flush();
			void end();
		};
	}
}