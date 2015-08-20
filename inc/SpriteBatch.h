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
		class Sprite;

		/**
		 * \brief sprite batcher class
		 * \author Moustapha Saad
		 */
		class SpriteBatch
		{
		private:
			///sprites limit
			static const unsigned int _limit = 2000;

			///sprite count
			unsigned int _count,vCount,iCount;

			///vertices set
			GXWrapper::VertexSet<Assets::Vertex2DPosColorTex> _vertices;
			///index set
			GXWrapper::IndexSet _indices;
			///geometry class
			GXWrapper::GeometryPtr _geometry;

			///current texture to be drawn
			GXWrapper::Texture2D* _texture;
			///current used shader
			GXWrapper::Shader* _shader;

			///indicates custom shader
			bool _customShader;

			///checks if it needs to flush sprites to GPU
			void checkFlush(GXWrapper::Texture2D* texture);
			///rotates a point
			glm::vec2 rotatePoint(glm::vec2 point, float angle);
		public:
			/**
			 * \brief default constructor
			 * \param shader custom shader (OPTIONAL)
			 * \author Moustapha Saad
			 */
			SpriteBatch(GXWrapper::ShaderPtr shader=nullptr);
			~SpriteBatch();

			///creates a new sprite instance
			std::shared_ptr<Sprite> newSprite(GXWrapper::Texture2DPtr tex=nullptr);
			///begin drawing batch
			void begin();

			/**
			 * \brief draw a sprite
			 * \param tex texture of the sprite
			 * \param x x position of the sprite
			 * \param y y postiion of the sprite
			 * \param color color of the sprite
			 * \auhtor Moustapha Saad
			 */
			void draw(GXWrapper::Texture2D*,int x, int y,GXWrapper::Color color);

			/**
			 * \brief draw a sprite
			 * \param tex texture of the sprite
			 * \param x x position of the sprite
			 * \param y y postiion of the sprite
			 * \param width width of the sprite
			 * \param height height of the sprite
			 * \param color color of the sprite
			 * \auhtor Moustapha Saad
			 */
			void draw(GXWrapper::Texture2D*,int x, int y,int width, int height,GXWrapper::Color color);

			/**
			 * \brief draw a sprite
			 * \param tex texture of the sprite
			 * \param dest destenation rectangle on screen
			 * \param angle angle of the sprite
			 * \param color color of the sprite
			 * \auhtor Moustapha Saad
			 */
			void draw(GXWrapper::Texture2D*,Rect dest,float angle,GXWrapper::Color color);

			/**
			 * \brief draw a sprite
			 * \param tex texture of the sprite
			 * \param dest destenation rect on screen
			 * \param src source rect from the texture
			 * \angle angle of rotation of the sprite
			 * \param color color of the sprite
			 * \auhtor Moustapha Saad
			 */
			void draw(GXWrapper::Texture2D*,Rect,Rect,float,GXWrapper::Color);

			///flushes the current sprites
			void flush();
			///ends the current batch
			void end();
		};
	}
}