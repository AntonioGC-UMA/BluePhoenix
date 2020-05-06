#pragma once

#include <unordered_map>

#include "Component.h"

namespace BP_ECS
{
	class Entity
	{
	public:
		template<class First, class Second, class... Types>
		bool has()
		{
			return has<First>() && has<Second, Types...>();
		}

		template<class T>
		bool has()
		{
			auto index = BaseComponent<T>::type;
			return components.find(index) != components.end();
		}


		template<class T>
		T* get()
		{
			components.at(BaseComponent<T>::type);
			T* res = dynamic_cast<T*>(components.at(BaseComponent<T>::type));

			return res;
		}
		
		void add(Component* c)
		{
			components[c->getType()] = c;
		}

	private:

		unordered_map<unsigned, Component*> components;
	};	
}
