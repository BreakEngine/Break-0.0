#pragma once
#include <vector>
#include <memory>
#include <string>
#include "IUpdateable.h"
#include "IDrawable.h"

namespace Break
{
	namespace Graphics
	{
		/**
		 * \brief main class of the scene tree every object is an entity
		 * \author Moustapha Saad
		 */
		class Entity: public GXWrapper::IUpdateable, public GXWrapper::IDrawable
		{
		private:
			/**
			 * \brief private copy constructor
			 */
			Entity(const Entity&other){}

			/**
			 * \brief generates a name of the entity
			 * \return name of entity
			 * \author Moustapha Saad
			 */
			std::string generateName()
			{
				static int ix = 1;
				return "Entity"+std::to_string(ix++);
			}
		protected:
			///children list
			std::vector<std::shared_ptr<Entity> > _children;

			///parent pointer
			Entity* _parent;

			///name of entity
			std::string _name;
		public:
			/**
			 * \brief default constructor
			 * \name name of the entity (OPTIONAL) - if no name provided then it will generate one
			 * \author Moustapha Saad
			 */
			Entity(std::string name="")
			{
				_parent = nullptr;
				if(name.size()>0)
					_name = name;
				else
					_name = generateName();
			}

			/**
			 * \brief virtaul destructor
			 * \author Moustapha Saad
			 */
			virtual ~Entity()
			{
				_children.clear();
			}

			/**
			 * \brief name getter
			 * \return name of the entity
			 * \author Moustapha Saad
			 */
			std::string getName()
			{
				return _name;
			}

			/**
			 * \brief performs DFS search for a child entity with a name
			 * \param name name of the entity that will be searched for
			 * \return pointer to Entity if found otherwise NULL
			 * \author Moustapha Saad
			 */
			Entity* find(std::string name)
			{
				for(auto child :_children){
					if(child->_name == name){
						return child.get();
					}else{
						auto res = child->find(name);
						if(res != NULL)
							return res;
					}
				}
				return NULL;
			}

			/**
			 * \brief input function that invokes children input function
			 *
			 * \author Moustapha Saad
			 */
			void input() override
			{
				for(auto child:_children)
					child->input();
			}

			/**
			 * \brief update function that invokes children update function
			 * \param tick time step that holds delta time and elapsed time
			 * \author Moustapha Saad
			 */
			void update(Infrastructure::TimeStep tick) override{
				for(auto child:_children)
					child->update(tick);
			}

			/**
			 * \brief draw function that invokes children draw function
			 *
			 * \author Moustapha Saad
			 */
			void draw() override{
				for(auto child:_children)
					child->draw();
			}

			/**
			 * \brief add child to children list
			 * \param child shared_ptr of Entity
			 *
			 * \author Moustapha Saad
			 */
			void addChild(std::shared_ptr<Entity> child)
			{
				_children.push_back(child);
				child->_parent = this;
			}
		};
	}
}