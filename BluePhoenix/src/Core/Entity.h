#pragma once

#include <unordered_map>
#include <vector>

#include "Component.h"

namespace BP_ECS
{
	class Entity
	{
	public:
		template<class... Types>
		bool has()
		{
			return (hasOne<Types>() && ...);
		}

		template<class T>
		bool hasOne()
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
