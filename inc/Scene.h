#pragma once
#include "Entity.h"
#include "SpriteBatch.h"
#include "Sprite.h"
#include "GlobalDefinitions.h"
namespace Break
{
	namespace Infrastructure
	{
		class Application;
	}
	namespace Graphics
	{
		///represents a scene node in entity graph
		class BREAK_API_EX Scene: public Entity
		{
			friend class Infrastructure::Application;
		protected:
			///scene spritebatch
			SpriteBatch* spriteBatch;
		public:

			///sprites list
			std::vector<SpritePtr> sprites;

			Scene(){spriteBatch = new SpriteBatch();}
			~Scene()
			{
				if(spriteBatch) delete spriteBatch;

				sprites.clear();
			}

			///adds sprite to children
			void addChild(SpritePtr sp)
			{
				sprites.push_back(sp);
			}

			///draws the whole scene
			void draw() override{

				Entity::draw();
				spriteBatch->begin();
				for(auto sprite:sprites)
					sprite->draw();
				spriteBatch->end();
			}

		};
	}
}