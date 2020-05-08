#pragma once

#include <unordered_map>
#include <vector>

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
			auto index = getType<T>();
			return components.find(index) != components.end();
		}


		template<class T>
		T* get()
		{
			T* res = dynamic_cast<T*>(components.at(getType<T>()));

			return res;
		}
		
		void add(unsigned listID, Component* cp)
		{
			components[listID] = cp;
		}

	private:

		unordered_map<unsigned, Component*> components;
	};	
}
