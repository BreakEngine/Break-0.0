#pragma once
#include "Texture2D.h"
#include "SpriteBatch.h"
#include "Entity.h"
#include <memory>
#include "GlobalDefinitions.h"

namespace Break
{
	namespace Graphics
	{


		/**
		 * \brief represnets a sprite object
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX Sprite : public Entity
		{
		public:
			virtual void input() override{
				Entity::input();
			}
			virtual void update(Infrastructure::TimeStep tick) override{

				Entity::update(tick);
			}
			virtual void draw() override
			{
				this->spriteBatch->draw(texture.get(),dest,src,angle,color);

				Entity::draw();
			}
		protected:
			///spirte texture
			GXWrapper::Texture2DPtr texture;

			///destenation rectangle, the rectangle of the screen that this sprite will be drawn to
			Rect dest;
			///source rectangle, the rectangle of the texture that this sprite will be mapped to
			Rect src;
			///angle of rotation
			float angle;
			///color tint of this sprite
			GXWrapper::Color color;

			///sprite batch handle
			SpriteBatch* spriteBatch;

		public:

			///default constrcutor
			Sprite(SpriteBatch* batcher)
			{
				spriteBatch = batcher;
				texture = nullptr;
				dest = Rect(0,0,0,0);
				src =  Rect(0,0,0,0);
				angle = 0;
				color = GXWrapper::Color(255,255,255,255);
			}

			Sprite(const Sprite& other)
			{
				this->texture = other.texture;
				this->spriteBatch = other.spriteBatch;
				this->color = other.color;
				this->angle = other.angle;
				this->dest = other.dest;
				this->src = other.src;
			}

			///texture init constructor
			Sprite(SpriteBatch* batcher, GXWrapper::Texture2DPtr tex)
			{
				spriteBatch = batcher;

				texture = tex;

				dest = Rect(0,0,texture->getWidth(),texture->getHeight());
				src =  Rect(0,0,texture->getWidth(),texture->getHeight());
				angle = 0;
				color = GXWrapper::Color(255,255,255,255);
			}

			GXWrapper::Color getColor()
			{
				return color;
			}

			void setColor(GXWrapper::Color c)
			{
				color =c;
			}
			void setRotation(float val)
			{
				angle = val;
			}

			float getRotation()
			{
				return angle;
			}

			glm::vec2 getPosition()
			{
				return glm::vec2(dest.x,dest.y);
			}

			void setPosition(float x, float y)
			{
				dest.x =x;
				dest.y = y;
			}

			glm::vec2 getSize()
			{
				return glm::vec2(dest.width,dest.height);
			}

			void setSize(float x,float y)
			{
				dest.width = x;
				dest.height = y;
			}

			GXWrapper::Texture2D* getTexture()
			{
				return texture.get();
			}

			void setTexture(GXWrapper::Texture2DPtr tex)
			{
				texture = tex;
			}

			Rect getSourceRect(){
				return src;
			}

			void setSourceRect(Rect val)
			{
				src = val;
			}

			~Sprite()
			{
				texture = nullptr;
			}


		};
		typedef std::shared_ptr<Sprite> SpritePtr;
	}
}