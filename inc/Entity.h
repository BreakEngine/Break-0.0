#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Component.hpp"
#include "IUpdateable.h"
#include "IDrawable.h"
#include "Transformable.h"
#include "GlobalDefinitions.h"

namespace Break
{
	namespace Graphics
	{
		/**
		 * \brief main class of the scene tree every object is an entity
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX Entity: public GXWrapper::IUpdateable,
			public GXWrapper::IDrawable, public Object,
			public Transformable
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

			///component list
			list<ComponentPtr> _components;

			///parent pointer
			Entity* _parent;
		public:

			/**
			 * \brief default constructor generates a unique name to the entity
			 * \author Moustapha Saad
			 */
			Entity():Object(generateName())
			{
				_parent = nullptr;
			}

			/**
			 * \brief default constructor
			 * \name name of the entity
			 * \author Moustapha Saad
			 */
			Entity(std::string name):Object(name)
			{
				_parent = nullptr;
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
			 * \brief finds a child with a specific name
			 * \param name name of the entity that will be searched for
			 * \return pointer to the child entity - null if not found
			 * \author Moustapha Saad
			 */
			Entity* find(std::string name)
			{
				for(auto child :_children){
					if(child->id == name){
						return child.get();
					}
				}
				return null;
			}

			/**
			 * \brief finds a child with a specific name
			 * \param name name of the entity that will be searched for
			 * \return list of the found children
			 * \author Moustapha Saad
			 */
			list<Entity*> find_all(std::string name)
			{
				list<Entity*> res;
				for(auto child :_children){
					if(child->id == name){
						res.push_back(child.get());
					}
				}
				return res;
			}

			/**
			 * \brief performs DFS search for a child entity with a name
			 * \param name name of the entity that will be searched for
			 * \return pointer to Entity if found otherwise NULL
			 * \author Moustapha Saad
			 */
			Entity* search(std::string name)
			{
				for(auto child :_children){
					if(child->id == name){
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
			 * \brief adds a component of type T passed in the template
			 * \author Moustapha Saad
			 */
			template<class T>
			void addComponent()
			{
				ComponentPtr component = std::make_shared<T>();
				component->gameEntity = this;
				_components.push_back(component);
			}

			list<Component*> getComponents(std::string id)
			{
				list<Component*> res;
				for(auto component : _components)
					if(component->id == id)
						res.push_back(component.get());
				return res;
			}
			/**
			 * \brief gets component with a name 'id'
			 * \param id id of the component
			 * \return pointer to the component - null if not found
			 * \author Moustapha Saad
			 */
			Component* getComponent(std::string id)
			{
				for(auto component : _components)
					if(component->id == id)
						return component.get();

				return nullptr;
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